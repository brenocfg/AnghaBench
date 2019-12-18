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
struct platform_device {int dummy; } ;
struct max8997_haptic {scalar_t__ mode; int /*<<< orphan*/  pwm; int /*<<< orphan*/  regulator; int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 scalar_t__ MAX8997_EXTERNAL_MODE ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct max8997_haptic*) ; 
 struct max8997_haptic* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8997_haptic_remove(struct platform_device *pdev)
{
	struct max8997_haptic *chip = platform_get_drvdata(pdev);

	input_unregister_device(chip->input_dev);
	regulator_put(chip->regulator);

	if (chip->mode == MAX8997_EXTERNAL_MODE)
		pwm_free(chip->pwm);

	kfree(chip);

	return 0;
}