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
struct rtw_pci {int /*<<< orphan*/  irq_lock; } ;
struct rtw_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_pci_disable_interrupt (struct rtw_dev*,struct rtw_pci*) ; 
 int /*<<< orphan*/  rtw_pci_dma_release (struct rtw_dev*,struct rtw_pci*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtw_pci_stop(struct rtw_dev *rtwdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	unsigned long flags;

	spin_lock_irqsave(&rtwpci->irq_lock, flags);
	rtw_pci_disable_interrupt(rtwdev, rtwpci);
	rtw_pci_dma_release(rtwdev, rtwpci);
	spin_unlock_irqrestore(&rtwpci->irq_lock, flags);
}