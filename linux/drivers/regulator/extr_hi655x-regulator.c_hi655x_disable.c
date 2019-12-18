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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct hi655x_regulator {int /*<<< orphan*/  disable_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 struct hi655x_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi655x_disable(struct regulator_dev *rdev)
{
	struct hi655x_regulator *regulator = rdev_get_drvdata(rdev);

	return regmap_write(rdev->regmap, regulator->disable_reg,
			    rdev->desc->enable_mask);
}