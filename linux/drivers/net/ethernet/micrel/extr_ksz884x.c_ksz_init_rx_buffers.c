#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ksz_desc_info {int alloc; } ;
struct ksz_hw {struct ksz_desc_info rx_desc_info; } ;
struct ksz_dma_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  dma; scalar_t__ skb; } ;
struct ksz_desc {int dummy; } ;
struct dev_info {int /*<<< orphan*/  pdev; int /*<<< orphan*/  mtu; struct ksz_hw hw; } ;

/* Variables and functions */
 struct ksz_dma_buf* DMA_BUFFER (struct ksz_desc*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma_buf (struct dev_info*,struct ksz_dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rx_pkt (struct ksz_desc_info*,struct ksz_desc**) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_desc (struct ksz_desc*) ; 
 int /*<<< orphan*/  set_rx_buf (struct ksz_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rx_len (struct ksz_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (scalar_t__) ; 

__attribute__((used)) static void ksz_init_rx_buffers(struct dev_info *adapter)
{
	int i;
	struct ksz_desc *desc;
	struct ksz_dma_buf *dma_buf;
	struct ksz_hw *hw = &adapter->hw;
	struct ksz_desc_info *info = &hw->rx_desc_info;

	for (i = 0; i < hw->rx_desc_info.alloc; i++) {
		get_rx_pkt(info, &desc);

		dma_buf = DMA_BUFFER(desc);
		if (dma_buf->skb && dma_buf->len != adapter->mtu)
			free_dma_buf(adapter, dma_buf, PCI_DMA_FROMDEVICE);
		dma_buf->len = adapter->mtu;
		if (!dma_buf->skb)
			dma_buf->skb = alloc_skb(dma_buf->len, GFP_ATOMIC);
		if (dma_buf->skb && !dma_buf->dma)
			dma_buf->dma = pci_map_single(
				adapter->pdev,
				skb_tail_pointer(dma_buf->skb),
				dma_buf->len,
				PCI_DMA_FROMDEVICE);

		/* Set descriptor. */
		set_rx_buf(desc, dma_buf->dma);
		set_rx_len(desc, dma_buf->len);
		release_desc(desc);
	}
}