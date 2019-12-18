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
struct megasas_instance {scalar_t__ unload; int issuepend_done; struct megasas_aen_event* ev; TYPE_1__* pdev; int /*<<< orphan*/ * aen_cmd; } ;
struct megasas_cmd {scalar_t__ abort_aen; } ;
struct megasas_aen_event {int /*<<< orphan*/  hotplug_work; struct megasas_instance* instance; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct megasas_aen_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_aen_polling ; 
 int /*<<< orphan*/  megasas_async_queue ; 
 int /*<<< orphan*/  megasas_poll_wait ; 
 int megasas_poll_wait_aen ; 
 int /*<<< orphan*/  megasas_return_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  poll_aen_lock ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
megasas_service_aen(struct megasas_instance *instance, struct megasas_cmd *cmd)
{
	unsigned long flags;

	/*
	 * Don't signal app if it is just an aborted previously registered aen
	 */
	if ((!cmd->abort_aen) && (instance->unload == 0)) {
		spin_lock_irqsave(&poll_aen_lock, flags);
		megasas_poll_wait_aen = 1;
		spin_unlock_irqrestore(&poll_aen_lock, flags);
		wake_up(&megasas_poll_wait);
		kill_fasync(&megasas_async_queue, SIGIO, POLL_IN);
	}
	else
		cmd->abort_aen = 0;

	instance->aen_cmd = NULL;

	megasas_return_cmd(instance, cmd);

	if ((instance->unload == 0) &&
		((instance->issuepend_done == 1))) {
		struct megasas_aen_event *ev;

		ev = kzalloc(sizeof(*ev), GFP_ATOMIC);
		if (!ev) {
			dev_err(&instance->pdev->dev, "megasas_service_aen: out of memory\n");
		} else {
			ev->instance = instance;
			instance->ev = ev;
			INIT_DELAYED_WORK(&ev->hotplug_work,
					  megasas_aen_polling);
			schedule_delayed_work(&ev->hotplug_work, 0);
		}
	}
}