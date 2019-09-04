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
struct nfp_fl_lag_group {int to_remove; int to_destroy; } ;
struct nfp_fl_lag {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NFP_FL_LAG_DELAY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfp_fl_lag_group* nfp_fl_lag_find_group_for_master_with_lag (struct nfp_fl_lag*,struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_fl_lag_schedule_group_delete(struct nfp_fl_lag *lag,
				 struct net_device *master)
{
	struct nfp_fl_lag_group *group;

	mutex_lock(&lag->lock);
	group = nfp_fl_lag_find_group_for_master_with_lag(lag, master);
	if (!group) {
		mutex_unlock(&lag->lock);
		return -ENOENT;
	}

	group->to_remove = true;
	group->to_destroy = true;
	mutex_unlock(&lag->lock);

	schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
	return 0;
}