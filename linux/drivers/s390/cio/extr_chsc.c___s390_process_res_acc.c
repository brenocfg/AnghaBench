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
struct subchannel {int /*<<< orphan*/  lock; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chp_event ) (struct subchannel*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHP_ONLINE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct subchannel*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __s390_process_res_acc(struct subchannel *sch, void *data)
{
	spin_lock_irq(sch->lock);
	if (sch->driver && sch->driver->chp_event)
		sch->driver->chp_event(sch, data, CHP_ONLINE);
	spin_unlock_irq(sch->lock);

	return 0;
}