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
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {scalar_t__ suspend_lo; scalar_t__ suspend_hi; int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  state; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CLUSTER_SUSPEND_READ_BALANCING ; 
 int READ ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int area_resyncing(struct mddev *mddev, int direction,
		sector_t lo, sector_t hi)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	int ret = 0;

	if ((direction == READ) &&
		test_bit(MD_CLUSTER_SUSPEND_READ_BALANCING, &cinfo->state))
		return 1;

	spin_lock_irq(&cinfo->suspend_lock);
	if (hi > cinfo->suspend_lo && lo < cinfo->suspend_hi)
		ret = 1;
	spin_unlock_irq(&cinfo->suspend_lock);
	return ret;
}