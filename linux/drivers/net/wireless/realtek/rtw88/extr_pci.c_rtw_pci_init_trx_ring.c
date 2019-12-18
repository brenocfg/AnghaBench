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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_pci_tx_ring {int dummy; } ;
struct rtw_pci_rx_ring {int dummy; } ;
struct rtw_pci {struct rtw_pci_rx_ring* rx_rings; struct rtw_pci_tx_ring* tx_rings; } ;
struct rtw_dev {struct rtw_chip_info* chip; scalar_t__ priv; } ;
struct rtw_chip_info {int tx_buf_desc_sz; int rx_buf_desc_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTK_MAX_RX_DESC_NUM ; 
 int RTK_MAX_RX_QUEUE_NUM ; 
 int RTK_MAX_TX_QUEUE_NUM ; 
 int /*<<< orphan*/  max_num_of_tx_queue (int) ; 
 int /*<<< orphan*/  rtw_pci_free_rx_ring (struct rtw_dev*,struct rtw_pci_rx_ring*) ; 
 int /*<<< orphan*/  rtw_pci_free_tx_ring (struct rtw_dev*,struct rtw_pci_tx_ring*) ; 
 int rtw_pci_init_rx_ring (struct rtw_dev*,struct rtw_pci_rx_ring*,int,int /*<<< orphan*/ ) ; 
 int rtw_pci_init_tx_ring (struct rtw_dev*,struct rtw_pci_tx_ring*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_pci_init_trx_ring(struct rtw_dev *rtwdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	struct rtw_pci_tx_ring *tx_ring;
	struct rtw_pci_rx_ring *rx_ring;
	struct rtw_chip_info *chip = rtwdev->chip;
	int i = 0, j = 0, tx_alloced = 0, rx_alloced = 0;
	int tx_desc_size, rx_desc_size;
	u32 len;
	int ret;

	tx_desc_size = chip->tx_buf_desc_sz;

	for (i = 0; i < RTK_MAX_TX_QUEUE_NUM; i++) {
		tx_ring = &rtwpci->tx_rings[i];
		len = max_num_of_tx_queue(i);
		ret = rtw_pci_init_tx_ring(rtwdev, tx_ring, tx_desc_size, len);
		if (ret)
			goto out;
	}

	rx_desc_size = chip->rx_buf_desc_sz;

	for (j = 0; j < RTK_MAX_RX_QUEUE_NUM; j++) {
		rx_ring = &rtwpci->rx_rings[j];
		ret = rtw_pci_init_rx_ring(rtwdev, rx_ring, rx_desc_size,
					   RTK_MAX_RX_DESC_NUM);
		if (ret)
			goto out;
	}

	return 0;

out:
	tx_alloced = i;
	for (i = 0; i < tx_alloced; i++) {
		tx_ring = &rtwpci->tx_rings[i];
		rtw_pci_free_tx_ring(rtwdev, tx_ring);
	}

	rx_alloced = j;
	for (j = 0; j < rx_alloced; j++) {
		rx_ring = &rtwpci->rx_rings[j];
		rtw_pci_free_rx_ring(rtwdev, rx_ring);
	}

	return ret;
}