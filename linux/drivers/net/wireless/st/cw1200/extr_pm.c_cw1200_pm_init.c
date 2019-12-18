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
struct cw1200_pm_state {int /*<<< orphan*/  stay_awake; int /*<<< orphan*/  lock; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_pm_stay_awake_tmo ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cw1200_pm_init(struct cw1200_pm_state *pm,
		   struct cw1200_common *priv)
{
	spin_lock_init(&pm->lock);

	timer_setup(&pm->stay_awake, cw1200_pm_stay_awake_tmo, 0);

	return 0;
}