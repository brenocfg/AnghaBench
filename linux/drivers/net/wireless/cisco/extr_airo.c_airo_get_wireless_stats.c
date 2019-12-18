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
struct net_device {struct airo_info* ml_priv; } ;
struct iw_statistics {int dummy; } ;
struct airo_info {struct iw_statistics wstats; int /*<<< orphan*/  thr_wait; int /*<<< orphan*/  jobs; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_WSTATS ; 
 int /*<<< orphan*/  airo_read_wireless_stats (struct airo_info*) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iw_statistics *airo_get_wireless_stats(struct net_device *dev)
{
	struct airo_info *local =  dev->ml_priv;

	if (!test_bit(JOB_WSTATS, &local->jobs)) {
		/* Get stats out of the card if available */
		if (down_trylock(&local->sem) != 0) {
			set_bit(JOB_WSTATS, &local->jobs);
			wake_up_interruptible(&local->thr_wait);
		} else
			airo_read_wireless_stats(local);
	}

	return &local->wstats;
}