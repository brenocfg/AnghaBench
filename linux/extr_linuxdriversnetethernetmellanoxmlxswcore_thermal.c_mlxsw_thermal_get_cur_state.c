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
typedef  int /*<<< orphan*/  u8 ;
struct thermal_cooling_device {struct mlxsw_thermal* devdata; } ;
struct mlxsw_thermal {int /*<<< orphan*/  core; TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MFSC_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mfsc ; 
 unsigned long mlxsw_duty_to_state (int /*<<< orphan*/ ) ; 
 int mlxsw_get_cooling_device_idx (struct mlxsw_thermal*,struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  mlxsw_reg_mfsc_pack (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mfsc_pwm_duty_cycle_get (char*) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_thermal_get_cur_state(struct thermal_cooling_device *cdev,
				       unsigned long *p_state)

{
	struct mlxsw_thermal *thermal = cdev->devdata;
	struct device *dev = thermal->bus_info->dev;
	char mfsc_pl[MLXSW_REG_MFSC_LEN];
	int err, idx;
	u8 duty;

	idx = mlxsw_get_cooling_device_idx(thermal, cdev);
	if (idx < 0)
		return idx;

	mlxsw_reg_mfsc_pack(mfsc_pl, idx, 0);
	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mfsc), mfsc_pl);
	if (err) {
		dev_err(dev, "Failed to query PWM duty\n");
		return err;
	}

	duty = mlxsw_reg_mfsc_pwm_duty_cycle_get(mfsc_pl);
	*p_state = mlxsw_duty_to_state(duty);
	return 0;
}