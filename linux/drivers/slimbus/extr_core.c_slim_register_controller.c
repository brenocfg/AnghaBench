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
struct TYPE_2__ {int /*<<< orphan*/  pause_comp; int /*<<< orphan*/  m_reconf; } ;
struct slim_controller {int id; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  txn_lock; TYPE_1__ sched; int /*<<< orphan*/  lock; int /*<<< orphan*/  tid_idr; int /*<<< orphan*/  laddr_ida; scalar_t__ max_cg; scalar_t__ min_cg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SLIM_MAX_CLK_GEAR ; 
 scalar_t__ SLIM_MIN_CLK_GEAR ; 
 int /*<<< orphan*/  ctrl_ida ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_register_slim_devices (struct slim_controller*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int slim_register_controller(struct slim_controller *ctrl)
{
	int id;

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	if (id < 0)
		return id;

	ctrl->id = id;

	if (!ctrl->min_cg)
		ctrl->min_cg = SLIM_MIN_CLK_GEAR;
	if (!ctrl->max_cg)
		ctrl->max_cg = SLIM_MAX_CLK_GEAR;

	ida_init(&ctrl->laddr_ida);
	idr_init(&ctrl->tid_idr);
	mutex_init(&ctrl->lock);
	mutex_init(&ctrl->sched.m_reconf);
	init_completion(&ctrl->sched.pause_comp);
	spin_lock_init(&ctrl->txn_lock);

	dev_dbg(ctrl->dev, "Bus [%s] registered:dev:%p\n",
		ctrl->name, ctrl->dev);

	of_register_slim_devices(ctrl);

	return 0;
}