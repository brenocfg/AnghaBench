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
struct regulator_haptic {int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct regulator_haptic* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  regulator_haptic_set_voltage (struct regulator_haptic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regulator_haptic_close(struct input_dev *input)
{
	struct regulator_haptic *haptic = input_get_drvdata(input);

	cancel_work_sync(&haptic->work);
	regulator_haptic_set_voltage(haptic, 0);
}