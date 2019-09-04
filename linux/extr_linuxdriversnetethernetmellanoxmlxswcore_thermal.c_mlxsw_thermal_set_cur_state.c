#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thermal_cooling_device {struct mlxsw_thermal* devdata; } ;
struct mlxsw_thermal {int /*<<< orphan*/  core; TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MFSC_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mfsc ; 
 int mlxsw_get_cooling_device_idx (struct mlxsw_thermal*,struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  mlxsw_reg_mfsc_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_state_to_duty (unsigned long) ; 

__attribute__((used)) static int mlxsw_thermal_set_cur_state(struct thermal_cooling_device *cdev,
				       unsigned long state)

{
	struct mlxsw_thermal *thermal = cdev->devdata;
	struct device *dev = thermal->bus_info->dev;
	char mfsc_pl[MLXSW_REG_MFSC_LEN];
	int err, idx;

	idx = mlxsw_get_cooling_device_idx(thermal, cdev);
	if (idx < 0)
		return idx;

	mlxsw_reg_mfsc_pack(mfsc_pl, idx, mlxsw_state_to_duty(state));
	err = mlxsw_reg_write(thermal->core, MLXSW_REG(mfsc), mfsc_pl);
	if (err) {
		dev_err(dev, "Failed to write PWM duty\n");
		return err;
	}
	return 0;
}