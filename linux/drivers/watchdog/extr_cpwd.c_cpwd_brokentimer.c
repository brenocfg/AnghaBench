#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct cpwd {TYPE_1__* devs; } ;
struct TYPE_7__ {int /*<<< orphan*/  expires; } ;
struct TYPE_6__ {int runstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  WD_BTIMEOUT ; 
 int WD_NUMDEVS ; 
 int WD_STAT_BSTOP ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct cpwd* cpwd_device ; 
 int /*<<< orphan*/  cpwd_resetbrokentimer (struct cpwd*,int) ; 
 TYPE_2__ cpwd_timer ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 scalar_t__ timer_pending (TYPE_2__*) ; 

__attribute__((used)) static void cpwd_brokentimer(struct timer_list *unused)
{
	struct cpwd *p = cpwd_device;
	int id, tripped = 0;

	/* kill a running timer instance, in case we
	 * were called directly instead of by kernel timer
	 */
	if (timer_pending(&cpwd_timer))
		del_timer(&cpwd_timer);

	for (id = 0; id < WD_NUMDEVS; id++) {
		if (p->devs[id].runstatus & WD_STAT_BSTOP) {
			++tripped;
			cpwd_resetbrokentimer(p, id);
		}
	}

	if (tripped) {
		/* there is at least one timer brokenstopped-- reschedule */
		cpwd_timer.expires = WD_BTIMEOUT;
		add_timer(&cpwd_timer);
	}
}