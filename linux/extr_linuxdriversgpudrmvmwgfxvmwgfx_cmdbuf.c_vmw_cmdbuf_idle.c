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
struct vmw_cmdbuf_man {TYPE_1__* dev_priv; int /*<<< orphan*/  idle_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmdbuf_waiters; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SVGA_IRQFLAG_COMMAND_BUFFER ; 
 int vmw_cmdbuf_cur_flush (struct vmw_cmdbuf_man*,int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_man_idle (struct vmw_cmdbuf_man*,int) ; 
 int /*<<< orphan*/  vmw_generic_waiter_add (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_generic_waiter_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

int vmw_cmdbuf_idle(struct vmw_cmdbuf_man *man, bool interruptible,
		    unsigned long timeout)
{
	int ret;

	ret = vmw_cmdbuf_cur_flush(man, interruptible);
	vmw_generic_waiter_add(man->dev_priv,
			       SVGA_IRQFLAG_COMMAND_BUFFER,
			       &man->dev_priv->cmdbuf_waiters);

	if (interruptible) {
		ret = wait_event_interruptible_timeout
			(man->idle_queue, vmw_cmdbuf_man_idle(man, true),
			 timeout);
	} else {
		ret = wait_event_timeout
			(man->idle_queue, vmw_cmdbuf_man_idle(man, true),
			 timeout);
	}
	vmw_generic_waiter_remove(man->dev_priv,
				  SVGA_IRQFLAG_COMMAND_BUFFER,
				  &man->dev_priv->cmdbuf_waiters);
	if (ret == 0) {
		if (!vmw_cmdbuf_man_idle(man, true))
			ret = -EBUSY;
		else
			ret = 0;
	}
	if (ret > 0)
		ret = 0;

	return ret;
}