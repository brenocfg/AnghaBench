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
struct rtw_pci {int /*<<< orphan*/ * irq_mask; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTK_PCI_HISR0 ; 
 int /*<<< orphan*/  RTK_PCI_HISR1 ; 
 int /*<<< orphan*/  RTK_PCI_HISR3 ; 
 int /*<<< orphan*/  rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_irq_recognized(struct rtw_dev *rtwdev,
				   struct rtw_pci *rtwpci, u32 *irq_status)
{
	irq_status[0] = rtw_read32(rtwdev, RTK_PCI_HISR0);
	irq_status[1] = rtw_read32(rtwdev, RTK_PCI_HISR1);
	irq_status[3] = rtw_read32(rtwdev, RTK_PCI_HISR3);
	irq_status[0] &= rtwpci->irq_mask[0];
	irq_status[1] &= rtwpci->irq_mask[1];
	irq_status[3] &= rtwpci->irq_mask[3];
	rtw_write32(rtwdev, RTK_PCI_HISR0, irq_status[0]);
	rtw_write32(rtwdev, RTK_PCI_HISR1, irq_status[1]);
	rtw_write32(rtwdev, RTK_PCI_HISR3, irq_status[3]);
}