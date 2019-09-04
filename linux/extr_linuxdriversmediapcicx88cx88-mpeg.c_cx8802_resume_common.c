#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  active; } ;
struct TYPE_3__ {int disabled; } ;
struct cx8802_dev {int /*<<< orphan*/  slock; TYPE_2__ mpegq; int /*<<< orphan*/  core; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  cx8802_restart_queue (struct cx8802_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  cx88_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct cx8802_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cx8802_resume_common(struct pci_dev *pci_dev)
{
	struct cx8802_dev *dev = pci_get_drvdata(pci_dev);
	unsigned long flags;
	int err;

	if (dev->state.disabled) {
		err = pci_enable_device(pci_dev);
		if (err) {
			pr_err("can't enable device\n");
			return err;
		}
		dev->state.disabled = 0;
	}
	err = pci_set_power_state(pci_dev, PCI_D0);
	if (err) {
		pr_err("can't enable device\n");
		pci_disable_device(pci_dev);
		dev->state.disabled = 1;

		return err;
	}
	pci_restore_state(pci_dev);

	/* FIXME: re-initialize hardware */
	cx88_reset(dev->core);

	/* restart video+vbi capture */
	spin_lock_irqsave(&dev->slock, flags);
	if (!list_empty(&dev->mpegq.active)) {
		pr_info("resume mpeg\n");
		cx8802_restart_queue(dev, &dev->mpegq);
	}
	spin_unlock_irqrestore(&dev->slock, flags);

	return 0;
}