#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct eadm_private {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 struct eadm_private* get_eadm_private (struct subchannel*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mod_timer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void eadm_subchannel_set_timeout(struct subchannel *sch, int expires)
{
	struct eadm_private *private = get_eadm_private(sch);

	if (expires == 0) {
		del_timer(&private->timer);
		return;
	}
	if (timer_pending(&private->timer)) {
		if (mod_timer(&private->timer, jiffies + expires))
			return;
	}
	private->timer.expires = jiffies + expires;
	add_timer(&private->timer);
}