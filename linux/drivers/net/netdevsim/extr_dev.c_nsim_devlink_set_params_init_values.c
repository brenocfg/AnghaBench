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
union devlink_param_value {int /*<<< orphan*/  vbool; int /*<<< orphan*/  vu32; } ;
struct nsim_dev {int /*<<< orphan*/  test1; int /*<<< orphan*/  max_macs; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_MAX_MACS ; 
 int /*<<< orphan*/  NSIM_DEVLINK_PARAM_ID_TEST1 ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 

__attribute__((used)) static void nsim_devlink_set_params_init_values(struct nsim_dev *nsim_dev,
						struct devlink *devlink)
{
	union devlink_param_value value;

	value.vu32 = nsim_dev->max_macs;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
					   value);
	value.vbool = nsim_dev->test1;
	devlink_param_driverinit_value_set(devlink,
					   NSIM_DEVLINK_PARAM_ID_TEST1,
					   value);
}