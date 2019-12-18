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
struct pci_dev {int dummy; } ;
struct hfi1_devdata {int /*<<< orphan*/  verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_dbg_ibdev_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_device_remove (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_unregister_ib_device (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_vnic_cleanup (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  ib_wq ; 
 struct hfi1_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  postinit_cleanup (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  shutdown_device (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  stop_timers (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  wait_for_clients (struct hfi1_devdata*) ; 

__attribute__((used)) static void remove_one(struct pci_dev *pdev)
{
	struct hfi1_devdata *dd = pci_get_drvdata(pdev);

	/* close debugfs files before ib unregister */
	hfi1_dbg_ibdev_exit(&dd->verbs_dev);

	/* remove the /dev hfi1 interface */
	hfi1_device_remove(dd);

	/* wait for existing user space clients to finish */
	wait_for_clients(dd);

	/* unregister from IB core */
	hfi1_unregister_ib_device(dd);

	/* cleanup vnic */
	hfi1_vnic_cleanup(dd);

	/*
	 * Disable the IB link, disable interrupts on the device,
	 * clear dma engines, etc.
	 */
	shutdown_device(dd);

	stop_timers(dd);

	/* wait until all of our (qsfp) queue_work() calls complete */
	flush_workqueue(ib_wq);

	postinit_cleanup(dd);
}