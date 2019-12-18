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
struct lima_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * regulator; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ ,char*) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lima_regulator_init(struct lima_device *dev)
{
	int ret;

	dev->regulator = devm_regulator_get_optional(dev->dev, "mali");
	if (IS_ERR(dev->regulator)) {
		ret = PTR_ERR(dev->regulator);
		dev->regulator = NULL;
		if (ret == -ENODEV)
			return 0;
		if (ret != -EPROBE_DEFER)
			dev_err(dev->dev, "failed to get regulator: %d\n", ret);
		return ret;
	}

	ret = regulator_enable(dev->regulator);
	if (ret < 0) {
		dev_err(dev->dev, "failed to enable regulator: %d\n", ret);
		return ret;
	}

	return 0;
}