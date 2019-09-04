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
struct hfi1_ibdev {int /*<<< orphan*/  mem_timer; int /*<<< orphan*/  memwait; int /*<<< orphan*/  txwait; int /*<<< orphan*/  rdi; } ;
struct hfi1_devdata {struct hfi1_ibdev verbs_dev; } ;

/* Variables and functions */
 scalar_t__ cntr_names_initialized ; 
 int /*<<< orphan*/  cntr_names_lock ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_cntr_names ; 
 int /*<<< orphan*/  hfi1_verbs_unregister_sysfs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * port_cntr_names ; 
 int /*<<< orphan*/  rvt_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbs_txreq_exit (struct hfi1_ibdev*) ; 

void hfi1_unregister_ib_device(struct hfi1_devdata *dd)
{
	struct hfi1_ibdev *dev = &dd->verbs_dev;

	hfi1_verbs_unregister_sysfs(dd);

	rvt_unregister_device(&dd->verbs_dev.rdi);

	if (!list_empty(&dev->txwait))
		dd_dev_err(dd, "txwait list not empty!\n");
	if (!list_empty(&dev->memwait))
		dd_dev_err(dd, "memwait list not empty!\n");

	del_timer_sync(&dev->mem_timer);
	verbs_txreq_exit(dev);

	mutex_lock(&cntr_names_lock);
	kfree(dev_cntr_names);
	kfree(port_cntr_names);
	dev_cntr_names = NULL;
	port_cntr_names = NULL;
	cntr_names_initialized = 0;
	mutex_unlock(&cntr_names_lock);
}