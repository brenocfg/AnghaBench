#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fcoe_sysfs_function_template {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct fcoe_ctlr_device {int id; int /*<<< orphan*/ * work_q; int /*<<< orphan*/ * devloss_work_q; TYPE_1__ dev; int /*<<< orphan*/  devloss_work_q_name; int /*<<< orphan*/  work_q_name; int /*<<< orphan*/  fcf_dev_loss_tmo; int /*<<< orphan*/  lock; int /*<<< orphan*/  fcfs; int /*<<< orphan*/  mode; struct fcoe_sysfs_function_template* f; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_CONN_TYPE_FABRIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 void* create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctlr_num ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  fcoe_bus_type ; 
 int /*<<< orphan*/  fcoe_ctlr_device_type ; 
 int /*<<< orphan*/  fcoe_fcf_dev_loss_tmo ; 
 int /*<<< orphan*/  kfree (struct fcoe_ctlr_device*) ; 
 struct fcoe_ctlr_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

struct fcoe_ctlr_device *fcoe_ctlr_device_add(struct device *parent,
				    struct fcoe_sysfs_function_template *f,
				    int priv_size)
{
	struct fcoe_ctlr_device *ctlr;
	int error = 0;

	ctlr = kzalloc(sizeof(struct fcoe_ctlr_device) + priv_size,
		       GFP_KERNEL);
	if (!ctlr)
		goto out;

	ctlr->id = atomic_inc_return(&ctlr_num) - 1;
	ctlr->f = f;
	ctlr->mode = FIP_CONN_TYPE_FABRIC;
	INIT_LIST_HEAD(&ctlr->fcfs);
	mutex_init(&ctlr->lock);
	ctlr->dev.parent = parent;
	ctlr->dev.bus = &fcoe_bus_type;
	ctlr->dev.type = &fcoe_ctlr_device_type;

	ctlr->fcf_dev_loss_tmo = fcoe_fcf_dev_loss_tmo;

	snprintf(ctlr->work_q_name, sizeof(ctlr->work_q_name),
		 "ctlr_wq_%d", ctlr->id);
	ctlr->work_q = create_singlethread_workqueue(
		ctlr->work_q_name);
	if (!ctlr->work_q)
		goto out_del;

	snprintf(ctlr->devloss_work_q_name,
		 sizeof(ctlr->devloss_work_q_name),
		 "ctlr_dl_wq_%d", ctlr->id);
	ctlr->devloss_work_q = create_singlethread_workqueue(
		ctlr->devloss_work_q_name);
	if (!ctlr->devloss_work_q)
		goto out_del_q;

	dev_set_name(&ctlr->dev, "ctlr_%d", ctlr->id);
	error = device_register(&ctlr->dev);
	if (error)
		goto out_del_q2;

	return ctlr;

out_del_q2:
	destroy_workqueue(ctlr->devloss_work_q);
	ctlr->devloss_work_q = NULL;
out_del_q:
	destroy_workqueue(ctlr->work_q);
	ctlr->work_q = NULL;
out_del:
	kfree(ctlr);
out:
	return NULL;
}