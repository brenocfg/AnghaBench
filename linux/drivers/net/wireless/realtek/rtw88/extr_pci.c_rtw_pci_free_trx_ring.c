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
struct rtw_pci_tx_ring {int dummy; } ;
struct rtw_pci_rx_ring {int dummy; } ;
struct rtw_pci {struct rtw_pci_rx_ring* rx_rings; struct rtw_pci_tx_ring* tx_rings; } ;
struct rtw_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int RTK_MAX_RX_QUEUE_NUM ; 
 int RTK_MAX_TX_QUEUE_NUM ; 
 int /*<<< orphan*/  rtw_pci_free_rx_ring (struct rtw_dev*,struct rtw_pci_rx_ring*) ; 
 int /*<<< orphan*/  rtw_pci_free_tx_ring (struct rtw_dev*,struct rtw_pci_tx_ring*) ; 

__attribute__((used)) static void rtw_pci_free_trx_ring(struct rtw_dev *rtwdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	struct rtw_pci_tx_ring *tx_ring;
	struct rtw_pci_rx_ring *rx_ring;
	int i;

	for (i = 0; i < RTK_MAX_TX_QUEUE_NUM; i++) {
		tx_ring = &rtwpci->tx_rings[i];
		rtw_pci_free_tx_ring(rtwdev, tx_ring);
	}

	for (i = 0; i < RTK_MAX_RX_QUEUE_NUM; i++) {
		rx_ring = &rtwpci->rx_rings[i];
		rtw_pci_free_rx_ring(rtwdev, rx_ring);
	}
}