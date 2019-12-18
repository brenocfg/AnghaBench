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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct controller {int power_fault_detected; int /*<<< orphan*/  requester; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  pending_events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DISABLE_SLOT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_ATTN_IND_ON ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_OFF ; 
 int PCI_EXP_SLTSTA_ABP ; 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int PCI_EXP_SLTSTA_PFD ; 
 int RERUN_ISR ; 
 int atomic_fetch_and (int,int /*<<< orphan*/ *) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_dev* ctrl_dev (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pciehp_handle_button_press (struct controller*) ; 
 int /*<<< orphan*/  pciehp_handle_disable_request (struct controller*) ; 
 int /*<<< orphan*/  pciehp_handle_presence_or_link_change (struct controller*,int) ; 
 int /*<<< orphan*/  pciehp_isr (int,void*) ; 
 int /*<<< orphan*/  pciehp_set_indicators (struct controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct controller*) ; 
 int /*<<< orphan*/  synchronize_hardirq (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pciehp_ist(int irq, void *dev_id)
{
	struct controller *ctrl = (struct controller *)dev_id;
	struct pci_dev *pdev = ctrl_dev(ctrl);
	irqreturn_t ret;
	u32 events;

	pci_config_pm_runtime_get(pdev);

	/* rerun pciehp_isr() if the port was inaccessible on interrupt */
	if (atomic_fetch_and(~RERUN_ISR, &ctrl->pending_events) & RERUN_ISR) {
		ret = pciehp_isr(irq, dev_id);
		enable_irq(irq);
		if (ret != IRQ_WAKE_THREAD) {
			pci_config_pm_runtime_put(pdev);
			return ret;
		}
	}

	synchronize_hardirq(irq);
	events = atomic_xchg(&ctrl->pending_events, 0);
	if (!events) {
		pci_config_pm_runtime_put(pdev);
		return IRQ_NONE;
	}

	/* Check Attention Button Pressed */
	if (events & PCI_EXP_SLTSTA_ABP) {
		ctrl_info(ctrl, "Slot(%s): Attention button pressed\n",
			  slot_name(ctrl));
		pciehp_handle_button_press(ctrl);
	}

	/* Check Power Fault Detected */
	if ((events & PCI_EXP_SLTSTA_PFD) && !ctrl->power_fault_detected) {
		ctrl->power_fault_detected = 1;
		ctrl_err(ctrl, "Slot(%s): Power fault\n", slot_name(ctrl));
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
				      PCI_EXP_SLTCTL_ATTN_IND_ON);
	}

	/*
	 * Disable requests have higher priority than Presence Detect Changed
	 * or Data Link Layer State Changed events.
	 */
	down_read(&ctrl->reset_lock);
	if (events & DISABLE_SLOT)
		pciehp_handle_disable_request(ctrl);
	else if (events & (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC))
		pciehp_handle_presence_or_link_change(ctrl, events);
	up_read(&ctrl->reset_lock);

	pci_config_pm_runtime_put(pdev);
	wake_up(&ctrl->requester);
	return IRQ_HANDLED;
}