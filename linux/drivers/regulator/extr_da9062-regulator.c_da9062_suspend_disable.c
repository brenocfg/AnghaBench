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
struct regulator_dev {int dummy; } ;
struct da9062_regulator {int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9062_suspend_disable(struct regulator_dev *rdev)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);

	return regmap_field_write(regl->suspend, 0);
}