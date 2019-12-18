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
struct chp_id {int dummy; } ;
struct chp_link {struct chp_id chpid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chp_event ) (struct subchannel*,struct chp_link*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHP_VARY_OFF ; 
 int /*<<< orphan*/  CHP_VARY_ON ; 
 int /*<<< orphan*/  memset (struct chp_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct subchannel*,struct chp_link*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __s390_subchannel_vary_chpid(struct subchannel *sch,
					 struct chp_id chpid, int on)
{
	unsigned long flags;
	struct chp_link link;

	memset(&link, 0, sizeof(struct chp_link));
	link.chpid = chpid;
	spin_lock_irqsave(sch->lock, flags);
	if (sch->driver && sch->driver->chp_event)
		sch->driver->chp_event(sch, &link,
				       on ? CHP_VARY_ON : CHP_VARY_OFF);
	spin_unlock_irqrestore(sch->lock, flags);
}