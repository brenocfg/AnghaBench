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
struct rtw_pci {int irq_enabled; int /*<<< orphan*/ * irq_mask; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTK_PCI_HIMR0 ; 
 int /*<<< orphan*/  RTK_PCI_HIMR1 ; 
 int /*<<< orphan*/  RTK_PCI_HIMR3 ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_enable_interrupt(struct rtw_dev *rtwdev,
				     struct rtw_pci *rtwpci)
{
	rtw_write32(rtwdev, RTK_PCI_HIMR0, rtwpci->irq_mask[0]);
	rtw_write32(rtwdev, RTK_PCI_HIMR1, rtwpci->irq_mask[1]);
	rtw_write32(rtwdev, RTK_PCI_HIMR3, rtwpci->irq_mask[3]);
	rtwpci->irq_enabled = true;
}