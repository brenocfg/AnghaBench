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
struct rtw_pci {scalar_t__ rx_tag; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT_RST_TRXDMA_INTF ; 
 int BIT_RX_TAG_EN ; 
 int /*<<< orphan*/  RTK_PCI_CTRL ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_pci_dma_reset(struct rtw_dev *rtwdev, struct rtw_pci *rtwpci)
{
	/* reset dma and rx tag */
	rtw_write32_set(rtwdev, RTK_PCI_CTRL,
			BIT_RST_TRXDMA_INTF | BIT_RX_TAG_EN);
	rtwpci->rx_tag = 0;
}