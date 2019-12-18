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
struct timer_list {int dummy; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  schid; } ;
struct eadm_private {struct subchannel* sch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EADM_LOG (int,char*) ; 
 int /*<<< orphan*/  EADM_LOG_HEX (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ eadm_subchannel_clear (struct subchannel*) ; 
 struct eadm_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct eadm_private* private ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void eadm_subchannel_timeout(struct timer_list *t)
{
	struct eadm_private *private = from_timer(private, t, timer);
	struct subchannel *sch = private->sch;

	spin_lock_irq(sch->lock);
	EADM_LOG(1, "timeout");
	EADM_LOG_HEX(1, &sch->schid, sizeof(sch->schid));
	if (eadm_subchannel_clear(sch))
		EADM_LOG(0, "clear failed");
	spin_unlock_irq(sch->lock);
}