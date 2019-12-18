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
struct nsim_dev {int /*<<< orphan*/  dummy_region; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSIM_DEV_DUMMY_REGION_SIZE ; 
 int /*<<< orphan*/  NSIM_DEV_DUMMY_REGION_SNAPSHOT_MAX ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_region_create (struct devlink*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsim_dev_dummy_region_init(struct nsim_dev *nsim_dev,
				      struct devlink *devlink)
{
	nsim_dev->dummy_region =
		devlink_region_create(devlink, "dummy",
				      NSIM_DEV_DUMMY_REGION_SNAPSHOT_MAX,
				      NSIM_DEV_DUMMY_REGION_SIZE);
	return PTR_ERR_OR_ZERO(nsim_dev->dummy_region);
}