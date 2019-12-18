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
struct pwm_device {int /*<<< orphan*/  label; } ;
struct pwm_chip {int base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_MISC ; 
 int /*<<< orphan*/  AB8500_PWM_OUT_CTRL7_REG ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ab8500_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	int ret;

	ret = abx500_mask_and_set_register_interruptible(chip->dev,
				AB8500_MISC, AB8500_PWM_OUT_CTRL7_REG,
				1 << (chip->base - 1), 0);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM, Error %d\n",
							pwm->label, ret);
}