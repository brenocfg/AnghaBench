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
struct iss_net_private {int /*<<< orphan*/  lock; scalar_t__ timer_val; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct iss_net_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_net_poll () ; 
 scalar_t__ jiffies ; 
 struct iss_net_private* lp ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void iss_net_timer(struct timer_list *t)
{
	struct iss_net_private *lp = from_timer(lp, t, timer);

	iss_net_poll();
	spin_lock(&lp->lock);
	mod_timer(&lp->timer, jiffies + lp->timer_val);
	spin_unlock(&lp->lock);
}