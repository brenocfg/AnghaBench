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
struct TYPE_3__ {int disabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  active; } ;
struct cx8802_dev {TYPE_1__ state; int /*<<< orphan*/  core; int /*<<< orphan*/  slock; TYPE_2__ mpegq; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cx8802_stop_dma (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx88_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct cx8802_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 scalar_t__ pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cx8802_suspend_common(struct pci_dev *pci_dev, pm_message_t state)
{
	struct cx8802_dev *dev = pci_get_drvdata(pci_dev);
	unsigned long flags;

	/* stop mpeg dma */
	spin_lock_irqsave(&dev->slock, flags);
	if (!list_empty(&dev->mpegq.active)) {
		dprintk(2, "suspend\n");
		pr_info("suspend mpeg\n");
		cx8802_stop_dma(dev);
	}
	spin_unlock_irqrestore(&dev->slock, flags);

	/* FIXME -- shutdown device */
	cx88_shutdown(dev->core);

	pci_save_state(pci_dev);
	if (pci_set_power_state(pci_dev,
				pci_choose_state(pci_dev, state)) != 0) {
		pci_disable_device(pci_dev);
		dev->state.disabled = 1;
	}
	return 0;
}