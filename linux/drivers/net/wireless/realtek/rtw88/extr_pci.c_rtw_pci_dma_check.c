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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ head; } ;
struct rtw_pci_rx_ring {TYPE_1__ r; } ;
struct rtw_pci_rx_buffer_desc {int /*<<< orphan*/  total_pkt_size; } ;
struct rtw_pci {int rx_tag; } ;
struct rtw_dev {struct rtw_chip_info* chip; scalar_t__ priv; } ;
struct rtw_chip_info {int rx_buf_desc_sz; } ;

/* Variables and functions */
 int RX_TAG_MAX ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_warn (struct rtw_dev*,char*) ; 

__attribute__((used)) static void rtw_pci_dma_check(struct rtw_dev *rtwdev,
			      struct rtw_pci_rx_ring *rx_ring,
			      u32 idx)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_pci_rx_buffer_desc *buf_desc;
	u32 desc_sz = chip->rx_buf_desc_sz;
	u16 total_pkt_size;

	buf_desc = (struct rtw_pci_rx_buffer_desc *)(rx_ring->r.head +
						     idx * desc_sz);
	total_pkt_size = le16_to_cpu(buf_desc->total_pkt_size);

	/* rx tag mismatch, throw a warning */
	if (total_pkt_size != rtwpci->rx_tag)
		rtw_warn(rtwdev, "pci bus timeout, check dma status\n");

	rtwpci->rx_tag = (rtwpci->rx_tag + 1) % RX_TAG_MAX;
}