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
struct sk_buff {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_tx_ring_info {struct bnxt_sw_tx_bd* tx_buf_ring; } ;
struct bnxt_sw_tx_bd {scalar_t__ action; int nr_frags; scalar_t__ is_push; struct sk_buff* skb; int /*<<< orphan*/ * xdpf; } ;
struct bnxt {int tx_nr_pages; int tx_nr_rings; int tx_nr_rings_xdp; int tx_ring_mask; int /*<<< orphan*/  dev; struct bnxt_tx_ring_info* tx_ring; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_DESC_CNT ; 
 scalar_t__ XDP_REDIRECT ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_tx_skbs(struct bnxt *bp)
{
	int i, max_idx;
	struct pci_dev *pdev = bp->pdev;

	if (!bp->tx_ring)
		return;

	max_idx = bp->tx_nr_pages * TX_DESC_CNT;
	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		int j;

		for (j = 0; j < max_idx;) {
			struct bnxt_sw_tx_bd *tx_buf = &txr->tx_buf_ring[j];
			struct sk_buff *skb;
			int k, last;

			if (i < bp->tx_nr_rings_xdp &&
			    tx_buf->action == XDP_REDIRECT) {
				dma_unmap_single(&pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					dma_unmap_len(tx_buf, len),
					PCI_DMA_TODEVICE);
				xdp_return_frame(tx_buf->xdpf);
				tx_buf->action = 0;
				tx_buf->xdpf = NULL;
				j++;
				continue;
			}

			skb = tx_buf->skb;
			if (!skb) {
				j++;
				continue;
			}

			tx_buf->skb = NULL;

			if (tx_buf->is_push) {
				dev_kfree_skb(skb);
				j += 2;
				continue;
			}

			dma_unmap_single(&pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 skb_headlen(skb),
					 PCI_DMA_TODEVICE);

			last = tx_buf->nr_frags;
			j += 2;
			for (k = 0; k < last; k++, j++) {
				int ring_idx = j & bp->tx_ring_mask;
				skb_frag_t *frag = &skb_shinfo(skb)->frags[k];

				tx_buf = &txr->tx_buf_ring[ring_idx];
				dma_unmap_page(
					&pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					skb_frag_size(frag), PCI_DMA_TODEVICE);
			}
			dev_kfree_skb(skb);
		}
		netdev_tx_reset_queue(netdev_get_tx_queue(bp->dev, i));
	}
}