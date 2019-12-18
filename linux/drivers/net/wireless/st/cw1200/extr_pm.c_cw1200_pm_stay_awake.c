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
struct TYPE_3__ {long expires; } ;
struct cw1200_pm_state {int /*<<< orphan*/  lock; TYPE_1__ stay_awake; } ;

/* Variables and functions */
 long jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void cw1200_pm_stay_awake(struct cw1200_pm_state *pm,
			  unsigned long tmo)
{
	long cur_tmo;
	spin_lock_bh(&pm->lock);
	cur_tmo = pm->stay_awake.expires - jiffies;
	if (!timer_pending(&pm->stay_awake) || cur_tmo < (long)tmo)
		mod_timer(&pm->stay_awake, jiffies + tmo);
	spin_unlock_bh(&pm->lock);
}