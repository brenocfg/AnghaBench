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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct cx88_core {int /*<<< orphan*/ * v4ldev; scalar_t__ ir; int /*<<< orphan*/ * kthread; } ;
struct cx8800_dev {int /*<<< orphan*/  pci; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx8800_unregister_video (struct cx8800_dev*) ; 
 int /*<<< orphan*/  cx88_core_put (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx88_ir_stop (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_shutdown (struct cx88_core*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cx8800_dev*) ; 
 int /*<<< orphan*/  kfree (struct cx8800_dev*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct cx8800_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void cx8800_finidev(struct pci_dev *pci_dev)
{
	struct cx8800_dev *dev = pci_get_drvdata(pci_dev);
	struct cx88_core *core = dev->core;

	/* stop thread */
	if (core->kthread) {
		kthread_stop(core->kthread);
		core->kthread = NULL;
	}

	if (core->ir)
		cx88_ir_stop(core);

	cx88_shutdown(core); /* FIXME */

	/* unregister stuff */

	free_irq(pci_dev->irq, dev);
	cx8800_unregister_video(dev);
	pci_disable_device(pci_dev);

	core->v4ldev = NULL;

	/* free memory */
	cx88_core_put(core, dev->pci);
	kfree(dev);
}