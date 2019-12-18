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
typedef  size_t u8 ;
struct rtw_pci_tx_ring {int dummy; } ;
struct rtw_pci {struct rtw_pci_tx_ring* tx_rings; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 size_t RTK_MAX_TX_QUEUE_NUM ; 
 int /*<<< orphan*/  rtw_pci_free_tx_ring_skbs (struct rtw_dev*,struct rtw_pci_tx_ring*) ; 

__attribute__((used)) static void rtw_pci_dma_release(struct rtw_dev *rtwdev, struct rtw_pci *rtwpci)
{
	struct rtw_pci_tx_ring *tx_ring;
	u8 queue;

	for (queue = 0; queue < RTK_MAX_TX_QUEUE_NUM; queue++) {
		tx_ring = &rtwpci->tx_rings[queue];
		rtw_pci_free_tx_ring_skbs(rtwdev, tx_ring);
	}
}