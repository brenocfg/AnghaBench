#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int gen; void* addr; } ;
union Vmxnet3_GenericDesc {void** dword; TYPE_3__ txd; } ;
typedef  int u32 ;
struct TYPE_9__ {int gen; int next2fill; union Vmxnet3_GenericDesc* base; } ;
struct TYPE_6__ {scalar_t__ basePA; } ;
struct vmxnet3_tx_queue {int txdata_desc_size; TYPE_4__ tx_ring; struct vmxnet3_tx_buf_info* buf_info; TYPE_1__ data_ring; } ;
struct vmxnet3_tx_ctx {int copy_size; union Vmxnet3_GenericDesc* sop_txd; union Vmxnet3_GenericDesc* eop_txd; } ;
struct vmxnet3_tx_buf_info {int len; int sop_idx; struct sk_buff* skb; scalar_t__ dma_addr; int /*<<< orphan*/  map_type; } ;
struct vmxnet3_adapter {int /*<<< orphan*/  netdev; TYPE_2__* pdev; } ;
struct sk_buff {scalar_t__ data; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_10__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  VMXNET3_MAP_NONE ; 
 int /*<<< orphan*/  VMXNET3_MAP_PAGE ; 
 int /*<<< orphan*/  VMXNET3_MAP_SINGLE ; 
 int VMXNET3_MAX_TX_BUF_SIZE ; 
 int VMXNET3_TXD_GEN_SHIFT ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (void*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vmxnet3_cmd_ring_adv_next2fill (TYPE_4__*) ; 

__attribute__((used)) static int
vmxnet3_map_pkt(struct sk_buff *skb, struct vmxnet3_tx_ctx *ctx,
		struct vmxnet3_tx_queue *tq, struct pci_dev *pdev,
		struct vmxnet3_adapter *adapter)
{
	u32 dw2, len;
	unsigned long buf_offset;
	int i;
	union Vmxnet3_GenericDesc *gdesc;
	struct vmxnet3_tx_buf_info *tbi = NULL;

	BUG_ON(ctx->copy_size > skb_headlen(skb));

	/* use the previous gen bit for the SOP desc */
	dw2 = (tq->tx_ring.gen ^ 0x1) << VMXNET3_TXD_GEN_SHIFT;

	ctx->sop_txd = tq->tx_ring.base + tq->tx_ring.next2fill;
	gdesc = ctx->sop_txd; /* both loops below can be skipped */

	/* no need to map the buffer if headers are copied */
	if (ctx->copy_size) {
		ctx->sop_txd->txd.addr = cpu_to_le64(tq->data_ring.basePA +
					tq->tx_ring.next2fill *
					tq->txdata_desc_size);
		ctx->sop_txd->dword[2] = cpu_to_le32(dw2 | ctx->copy_size);
		ctx->sop_txd->dword[3] = 0;

		tbi = tq->buf_info + tq->tx_ring.next2fill;
		tbi->map_type = VMXNET3_MAP_NONE;

		netdev_dbg(adapter->netdev,
			"txd[%u]: 0x%Lx 0x%x 0x%x\n",
			tq->tx_ring.next2fill,
			le64_to_cpu(ctx->sop_txd->txd.addr),
			ctx->sop_txd->dword[2], ctx->sop_txd->dword[3]);
		vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);

		/* use the right gen for non-SOP desc */
		dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;
	}

	/* linear part can use multiple tx desc if it's big */
	len = skb_headlen(skb) - ctx->copy_size;
	buf_offset = ctx->copy_size;
	while (len) {
		u32 buf_size;

		if (len < VMXNET3_MAX_TX_BUF_SIZE) {
			buf_size = len;
			dw2 |= len;
		} else {
			buf_size = VMXNET3_MAX_TX_BUF_SIZE;
			/* spec says that for TxDesc.len, 0 == 2^14 */
		}

		tbi = tq->buf_info + tq->tx_ring.next2fill;
		tbi->map_type = VMXNET3_MAP_SINGLE;
		tbi->dma_addr = dma_map_single(&adapter->pdev->dev,
				skb->data + buf_offset, buf_size,
				PCI_DMA_TODEVICE);
		if (dma_mapping_error(&adapter->pdev->dev, tbi->dma_addr))
			return -EFAULT;

		tbi->len = buf_size;

		gdesc = tq->tx_ring.base + tq->tx_ring.next2fill;
		BUG_ON(gdesc->txd.gen == tq->tx_ring.gen);

		gdesc->txd.addr = cpu_to_le64(tbi->dma_addr);
		gdesc->dword[2] = cpu_to_le32(dw2);
		gdesc->dword[3] = 0;

		netdev_dbg(adapter->netdev,
			"txd[%u]: 0x%Lx 0x%x 0x%x\n",
			tq->tx_ring.next2fill, le64_to_cpu(gdesc->txd.addr),
			le32_to_cpu(gdesc->dword[2]), gdesc->dword[3]);
		vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);
		dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;

		len -= buf_size;
		buf_offset += buf_size;
	}

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 buf_size;

		buf_offset = 0;
		len = skb_frag_size(frag);
		while (len) {
			tbi = tq->buf_info + tq->tx_ring.next2fill;
			if (len < VMXNET3_MAX_TX_BUF_SIZE) {
				buf_size = len;
				dw2 |= len;
			} else {
				buf_size = VMXNET3_MAX_TX_BUF_SIZE;
				/* spec says that for TxDesc.len, 0 == 2^14 */
			}
			tbi->map_type = VMXNET3_MAP_PAGE;
			tbi->dma_addr = skb_frag_dma_map(&adapter->pdev->dev, frag,
							 buf_offset, buf_size,
							 DMA_TO_DEVICE);
			if (dma_mapping_error(&adapter->pdev->dev, tbi->dma_addr))
				return -EFAULT;

			tbi->len = buf_size;

			gdesc = tq->tx_ring.base + tq->tx_ring.next2fill;
			BUG_ON(gdesc->txd.gen == tq->tx_ring.gen);

			gdesc->txd.addr = cpu_to_le64(tbi->dma_addr);
			gdesc->dword[2] = cpu_to_le32(dw2);
			gdesc->dword[3] = 0;

			netdev_dbg(adapter->netdev,
				"txd[%u]: 0x%llx %u %u\n",
				tq->tx_ring.next2fill, le64_to_cpu(gdesc->txd.addr),
				le32_to_cpu(gdesc->dword[2]), gdesc->dword[3]);
			vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);
			dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;

			len -= buf_size;
			buf_offset += buf_size;
		}
	}

	ctx->eop_txd = gdesc;

	/* set the last buf_info for the pkt */
	tbi->skb = skb;
	tbi->sop_idx = ctx->sop_txd - tq->tx_ring.base;

	return 0;
}