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
struct rtw_pci {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_enabled; } ;
struct rtw_dev {scalar_t__ priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  rtw_pci_disable_interrupt (struct rtw_dev*,struct rtw_pci*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rtw_pci_interrupt_handler(int irq, void *dev)
{
	struct rtw_dev *rtwdev = dev;
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;

	spin_lock(&rtwpci->irq_lock);
	if (!rtwpci->irq_enabled)
		goto out;

	/* disable RTW PCI interrupt to avoid more interrupts before the end of
	 * thread function
	 *
	 * disable HIMR here to also avoid new HISR flag being raised before
	 * the HISRs have been Write-1-cleared for MSI. If not all of the HISRs
	 * are cleared, the edge-triggered interrupt will not be generated when
	 * a new HISR flag is set.
	 */
	rtw_pci_disable_interrupt(rtwdev, rtwpci);
out:
	spin_unlock(&rtwpci->irq_lock);

	return IRQ_WAKE_THREAD;
}