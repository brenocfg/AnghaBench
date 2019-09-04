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
struct max77693_haptic {int /*<<< orphan*/  dev; int /*<<< orphan*/  motor_reg; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77693_haptic* input_get_drvdata (struct input_dev*) ; 
 int max77843_haptic_bias (struct max77693_haptic*,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77693_haptic_open(struct input_dev *dev)
{
	struct max77693_haptic *haptic = input_get_drvdata(dev);
	int error;

	error = max77843_haptic_bias(haptic, true);
	if (error)
		return error;

	error = regulator_enable(haptic->motor_reg);
	if (error) {
		dev_err(haptic->dev,
			"failed to enable regulator: %d\n", error);
		return error;
	}

	return 0;
}