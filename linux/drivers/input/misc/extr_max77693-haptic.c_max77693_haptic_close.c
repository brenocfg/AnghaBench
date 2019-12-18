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
struct max77693_haptic {int /*<<< orphan*/  dev; int /*<<< orphan*/  motor_reg; int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77693_haptic* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  max77693_haptic_disable (struct max77693_haptic*) ; 
 int /*<<< orphan*/  max77843_haptic_bias (struct max77693_haptic*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77693_haptic_close(struct input_dev *dev)
{
	struct max77693_haptic *haptic = input_get_drvdata(dev);
	int error;

	cancel_work_sync(&haptic->work);
	max77693_haptic_disable(haptic);

	error = regulator_disable(haptic->motor_reg);
	if (error)
		dev_err(haptic->dev,
			"failed to disable regulator: %d\n", error);

	max77843_haptic_bias(haptic, false);
}