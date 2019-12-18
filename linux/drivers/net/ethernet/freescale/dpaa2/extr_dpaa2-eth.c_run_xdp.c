#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xdp_buff {void* data; void* data_end; void* data_hard_start; int /*<<< orphan*/ * rxq; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {TYPE_4__* net_dev; int /*<<< orphan*/  percpu_stats; } ;
struct dpaa2_eth_fq {int /*<<< orphan*/  flowid; } ;
struct TYPE_8__ {int res; int /*<<< orphan*/  prog; } ;
struct TYPE_7__ {int /*<<< orphan*/  xdp_redirect; int /*<<< orphan*/  xdp_drop; int /*<<< orphan*/  xdp_tx; int /*<<< orphan*/  xdp_tx_err; } ;
struct dpaa2_eth_channel {TYPE_3__ xdp; TYPE_2__ stats; int /*<<< orphan*/  buf_count; int /*<<< orphan*/  xdp_rxq; } ;
struct bpf_prog {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_SIZE ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
 int XDP_PACKET_HEADROOM ; 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fd_get_addr (struct dpaa2_fd*) ; 
 int dpaa2_fd_get_len (struct dpaa2_fd*) ; 
 int dpaa2_fd_get_offset (struct dpaa2_fd*) ; 
 int /*<<< orphan*/  dpaa2_fd_set_len (struct dpaa2_fd*,int) ; 
 int /*<<< orphan*/  dpaa2_fd_set_offset (struct dpaa2_fd*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rtnl_link_stats64* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xdp_exception (TYPE_4__*,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int xdp_do_redirect (TYPE_4__*,struct xdp_buff*,struct bpf_prog*) ; 
 int xdp_enqueue (struct dpaa2_eth_priv*,struct dpaa2_fd*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_release_buf (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_set_data_meta_invalid (struct xdp_buff*) ; 

__attribute__((used)) static u32 run_xdp(struct dpaa2_eth_priv *priv,
		   struct dpaa2_eth_channel *ch,
		   struct dpaa2_eth_fq *rx_fq,
		   struct dpaa2_fd *fd, void *vaddr)
{
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	struct rtnl_link_stats64 *percpu_stats;
	struct bpf_prog *xdp_prog;
	struct xdp_buff xdp;
	u32 xdp_act = XDP_PASS;
	int err;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);

	rcu_read_lock();

	xdp_prog = READ_ONCE(ch->xdp.prog);
	if (!xdp_prog)
		goto out;

	xdp.data = vaddr + dpaa2_fd_get_offset(fd);
	xdp.data_end = xdp.data + dpaa2_fd_get_len(fd);
	xdp.data_hard_start = xdp.data - XDP_PACKET_HEADROOM;
	xdp_set_data_meta_invalid(&xdp);
	xdp.rxq = &ch->xdp_rxq;

	xdp_act = bpf_prog_run_xdp(xdp_prog, &xdp);

	/* xdp.data pointer may have changed */
	dpaa2_fd_set_offset(fd, xdp.data - vaddr);
	dpaa2_fd_set_len(fd, xdp.data_end - xdp.data);

	switch (xdp_act) {
	case XDP_PASS:
		break;
	case XDP_TX:
		err = xdp_enqueue(priv, fd, vaddr, rx_fq->flowid);
		if (err) {
			xdp_release_buf(priv, ch, addr);
			percpu_stats->tx_errors++;
			ch->stats.xdp_tx_err++;
		} else {
			percpu_stats->tx_packets++;
			percpu_stats->tx_bytes += dpaa2_fd_get_len(fd);
			ch->stats.xdp_tx++;
		}
		break;
	default:
		bpf_warn_invalid_xdp_action(xdp_act);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(priv->net_dev, xdp_prog, xdp_act);
		/* fall through */
	case XDP_DROP:
		xdp_release_buf(priv, ch, addr);
		ch->stats.xdp_drop++;
		break;
	case XDP_REDIRECT:
		dma_unmap_page(priv->net_dev->dev.parent, addr,
			       DPAA2_ETH_RX_BUF_SIZE, DMA_BIDIRECTIONAL);
		ch->buf_count--;
		xdp.data_hard_start = vaddr;
		err = xdp_do_redirect(priv->net_dev, &xdp, xdp_prog);
		if (unlikely(err))
			ch->stats.xdp_drop++;
		else
			ch->stats.xdp_redirect++;
		break;
	}

	ch->xdp.res |= xdp_act;
out:
	rcu_read_unlock();
	return xdp_act;
}