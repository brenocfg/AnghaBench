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
struct sk_buff {scalar_t__ cb; } ;
struct rtl_priv {scalar_t__ use_new_trx_flow; } ;
struct rtl_pci {int rxringcount; TYPE_1__* rx_ring; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rxbuffersize; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/ * buffer_desc; struct sk_buff** rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_pci_free_rx_ring(struct ieee80211_hw *hw, int rxring_idx)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	int i;

	/* free every desc in this ring */
	for (i = 0; i < rtlpci->rxringcount; i++) {
		struct sk_buff *skb = rtlpci->rx_ring[rxring_idx].rx_buf[i];

		if (!skb)
			continue;
		pci_unmap_single(rtlpci->pdev, *((dma_addr_t *)skb->cb),
				 rtlpci->rxbuffersize, PCI_DMA_FROMDEVICE);
		kfree_skb(skb);
	}

	/* free dma of this ring */
	if (rtlpriv->use_new_trx_flow) {
		pci_free_consistent(rtlpci->pdev,
				    sizeof(*rtlpci->rx_ring[rxring_idx].
				    buffer_desc) * rtlpci->rxringcount,
				    rtlpci->rx_ring[rxring_idx].buffer_desc,
				    rtlpci->rx_ring[rxring_idx].dma);
		rtlpci->rx_ring[rxring_idx].buffer_desc = NULL;
	} else {
		pci_free_consistent(rtlpci->pdev,
				    sizeof(*rtlpci->rx_ring[rxring_idx].desc) *
				    rtlpci->rxringcount,
				    rtlpci->rx_ring[rxring_idx].desc,
				    rtlpci->rx_ring[rxring_idx].dma);
		rtlpci->rx_ring[rxring_idx].desc = NULL;
	}
}