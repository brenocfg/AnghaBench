#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct xdp_buff {void* data; void* data_end; int /*<<< orphan*/ * rxq; int /*<<< orphan*/  data_hard_start; } ;
struct snd_queue {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rcv_queue {int /*<<< orphan*/  xdp_rxq; } ;
struct page {int dummy; } ;
struct nicvf {TYPE_1__* pdev; int /*<<< orphan*/  netdev; } ;
struct cqe_rx_t {scalar_t__ align_pad; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_MASK ; 
 scalar_t__ RCV_FRAG_LEN ; 
#define  XDP_ABORTED 131 
#define  XDP_DROP 130 
 scalar_t__ XDP_PACKET_HEADROOM ; 
#define  XDP_PASS 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nicvf_iova_to_phys (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_xdp_sq_append_pkt (struct nicvf*,struct snd_queue*,int,int,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  phys_to_virt (int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 struct page* virt_to_page (void*) ; 
 int /*<<< orphan*/  xdp_set_data_meta_invalid (struct xdp_buff*) ; 

__attribute__((used)) static inline bool nicvf_xdp_rx(struct nicvf *nic, struct bpf_prog *prog,
				struct cqe_rx_t *cqe_rx, struct snd_queue *sq,
				struct rcv_queue *rq, struct sk_buff **skb)
{
	struct xdp_buff xdp;
	struct page *page;
	u32 action;
	u16 len, offset = 0;
	u64 dma_addr, cpu_addr;
	void *orig_data;

	/* Retrieve packet buffer's DMA address and length */
	len = *((u16 *)((void *)cqe_rx + (3 * sizeof(u64))));
	dma_addr = *((u64 *)((void *)cqe_rx + (7 * sizeof(u64))));

	cpu_addr = nicvf_iova_to_phys(nic, dma_addr);
	if (!cpu_addr)
		return false;
	cpu_addr = (u64)phys_to_virt(cpu_addr);
	page = virt_to_page((void *)cpu_addr);

	xdp.data_hard_start = page_address(page);
	xdp.data = (void *)cpu_addr;
	xdp_set_data_meta_invalid(&xdp);
	xdp.data_end = xdp.data + len;
	xdp.rxq = &rq->xdp_rxq;
	orig_data = xdp.data;

	rcu_read_lock();
	action = bpf_prog_run_xdp(prog, &xdp);
	rcu_read_unlock();

	len = xdp.data_end - xdp.data;
	/* Check if XDP program has changed headers */
	if (orig_data != xdp.data) {
		offset = orig_data - xdp.data;
		dma_addr -= offset;
	}

	switch (action) {
	case XDP_PASS:
		/* Check if it's a recycled page, if not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		if (page_ref_count(page) == 1) {
			dma_addr &= PAGE_MASK;
			dma_unmap_page_attrs(&nic->pdev->dev, dma_addr,
					     RCV_FRAG_LEN + XDP_PACKET_HEADROOM,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
		}

		/* Build SKB and pass on packet to network stack */
		*skb = build_skb(xdp.data,
				 RCV_FRAG_LEN - cqe_rx->align_pad + offset);
		if (!*skb)
			put_page(page);
		else
			skb_put(*skb, len);
		return false;
	case XDP_TX:
		nicvf_xdp_sq_append_pkt(nic, sq, (u64)xdp.data, dma_addr, len);
		return true;
	default:
		bpf_warn_invalid_xdp_action(action);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(nic->netdev, prog, action);
		/* fall through */
	case XDP_DROP:
		/* Check if it's a recycled page, if not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		if (page_ref_count(page) == 1) {
			dma_addr &= PAGE_MASK;
			dma_unmap_page_attrs(&nic->pdev->dev, dma_addr,
					     RCV_FRAG_LEN + XDP_PACKET_HEADROOM,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
		}
		put_page(page);
		return true;
	}
	return false;
}