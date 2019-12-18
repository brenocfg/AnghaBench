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
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
typedef  enum vexpress_reset_func { ____Placeholder_vexpress_reset_func } vexpress_reset_func ;

/* Variables and functions */
 int EINVAL ; 
#define  FUNC_REBOOT 130 
#define  FUNC_RESET 129 
#define  FUNC_SHUTDOWN 128 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int _vexpress_register_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct regmap*) ; 
 struct regmap* devm_regmap_init_vexpress_config (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_power_off ; 
 int /*<<< orphan*/  vexpress_power_off ; 
 int /*<<< orphan*/ * vexpress_power_off_device ; 
 int /*<<< orphan*/  vexpress_reset_of_match ; 
 int /*<<< orphan*/  vexpress_restart_device ; 

__attribute__((used)) static int vexpress_reset_probe(struct platform_device *pdev)
{
	const struct of_device_id *match =
			of_match_device(vexpress_reset_of_match, &pdev->dev);
	struct regmap *regmap;
	int ret = 0;

	if (!match)
		return -EINVAL;

	regmap = devm_regmap_init_vexpress_config(&pdev->dev);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);
	dev_set_drvdata(&pdev->dev, regmap);

	switch ((enum vexpress_reset_func)match->data) {
	case FUNC_SHUTDOWN:
		vexpress_power_off_device = &pdev->dev;
		pm_power_off = vexpress_power_off;
		break;
	case FUNC_RESET:
		if (!vexpress_restart_device)
			ret = _vexpress_register_restart_handler(&pdev->dev);
		break;
	case FUNC_REBOOT:
		ret = _vexpress_register_restart_handler(&pdev->dev);
		break;
	};

	return ret;
}