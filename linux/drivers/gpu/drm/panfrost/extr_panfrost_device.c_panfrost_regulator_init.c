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
struct panfrost_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  regulator; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_regulator_init(struct panfrost_device *pfdev)
{
	int ret;

	pfdev->regulator = devm_regulator_get(pfdev->dev, "mali");
	if (IS_ERR(pfdev->regulator)) {
		ret = PTR_ERR(pfdev->regulator);
		dev_err(pfdev->dev, "failed to get regulator: %d\n", ret);
		return ret;
	}

	ret = regulator_enable(pfdev->regulator);
	if (ret < 0) {
		dev_err(pfdev->dev, "failed to enable regulator: %d\n", ret);
		return ret;
	}

	return 0;
}