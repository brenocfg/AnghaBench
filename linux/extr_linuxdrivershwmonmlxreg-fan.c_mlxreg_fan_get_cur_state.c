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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_cooling_device {struct mlxreg_fan* devdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct mlxreg_fan {int /*<<< orphan*/  dev; TYPE_1__ pwm; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned long MLXREG_FAN_PWM_DUTY2STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxreg_fan_get_cur_state(struct thermal_cooling_device *cdev,
				    unsigned long *state)

{
	struct mlxreg_fan *fan = cdev->devdata;
	u32 regval;
	int err;

	err = regmap_read(fan->regmap, fan->pwm.reg, &regval);
	if (err) {
		dev_err(fan->dev, "Failed to query PWM duty\n");
		return err;
	}

	*state = MLXREG_FAN_PWM_DUTY2STATE(regval);

	return 0;
}