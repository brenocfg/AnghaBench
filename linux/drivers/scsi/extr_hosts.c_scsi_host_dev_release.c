#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {struct device* parent; } ;
struct TYPE_2__ {scalar_t__ tags; } ;
struct Scsi_Host {scalar_t__ shost_state; int /*<<< orphan*/  host_no; struct Scsi_Host* shost_data; TYPE_1__ tag_set; int /*<<< orphan*/  shost_dev; scalar_t__ work_q; scalar_t__ ehandler; scalar_t__ tmf_work_q; int /*<<< orphan*/  hostt; } ;

/* Variables and functions */
 scalar_t__ SHOST_CREATED ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 struct Scsi_Host* dev_name (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  host_index_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct Scsi_Host*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  scsi_mq_destroy_tags (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_proc_hostdir_rm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_host_dev_release(struct device *dev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct device *parent = dev->parent;

	scsi_proc_hostdir_rm(shost->hostt);

	/* Wait for functions invoked through call_rcu(&shost->rcu, ...) */
	rcu_barrier();

	if (shost->tmf_work_q)
		destroy_workqueue(shost->tmf_work_q);
	if (shost->ehandler)
		kthread_stop(shost->ehandler);
	if (shost->work_q)
		destroy_workqueue(shost->work_q);

	if (shost->shost_state == SHOST_CREATED) {
		/*
		 * Free the shost_dev device name here if scsi_host_alloc()
		 * and scsi_host_put() have been called but neither
		 * scsi_host_add() nor scsi_host_remove() has been called.
		 * This avoids that the memory allocated for the shost_dev
		 * name is leaked.
		 */
		kfree(dev_name(&shost->shost_dev));
	}

	if (shost->tag_set.tags)
		scsi_mq_destroy_tags(shost);

	kfree(shost->shost_data);

	ida_simple_remove(&host_index_ida, shost->host_no);

	if (parent)
		put_device(parent);
	kfree(shost);
}