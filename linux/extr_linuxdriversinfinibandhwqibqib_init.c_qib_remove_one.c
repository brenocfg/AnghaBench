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
struct qib_devdata {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wq ; 
 struct qib_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int) ; 
 int /*<<< orphan*/  qib_device_remove (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_mini_init ; 
 int /*<<< orphan*/  qib_postinit_cleanup (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_shutdown_device (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_stop_timers (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_unregister_ib_device (struct qib_devdata*) ; 
 int qibfs_remove (struct qib_devdata*) ; 

__attribute__((used)) static void qib_remove_one(struct pci_dev *pdev)
{
	struct qib_devdata *dd = pci_get_drvdata(pdev);
	int ret;

	/* unregister from IB core */
	qib_unregister_ib_device(dd);

	/*
	 * Disable the IB link, disable interrupts on the device,
	 * clear dma engines, etc.
	 */
	if (!qib_mini_init)
		qib_shutdown_device(dd);

	qib_stop_timers(dd);

	/* wait until all of our (qsfp) queue_work() calls complete */
	flush_workqueue(ib_wq);

	ret = qibfs_remove(dd);
	if (ret)
		qib_dev_err(dd, "Failed counters filesystem cleanup: %d\n",
			    -ret);

	qib_device_remove(dd);

	qib_postinit_cleanup(dd);
}