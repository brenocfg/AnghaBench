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
struct rvt_dev_info {int /*<<< orphan*/  n_mcast_grps_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void rvt_driver_mcast_init(struct rvt_dev_info *rdi)
{
	/*
	 * Anything that needs setup for multicast on a per driver or per rdi
	 * basis should be done in here.
	 */
	spin_lock_init(&rdi->n_mcast_grps_lock);
}