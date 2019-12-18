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
struct max8997_haptic {int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct max8997_haptic* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  max8997_haptic_disable (struct max8997_haptic*) ; 

__attribute__((used)) static void max8997_haptic_close(struct input_dev *dev)
{
	struct max8997_haptic *chip = input_get_drvdata(dev);

	cancel_work_sync(&chip->work);
	max8997_haptic_disable(chip);
}