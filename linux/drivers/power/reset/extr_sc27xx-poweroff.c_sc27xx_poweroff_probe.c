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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_power_off ; 
 int /*<<< orphan*/  poweroff_syscore_ops ; 
 int /*<<< orphan*/  register_syscore_ops (int /*<<< orphan*/ *) ; 
 scalar_t__ regmap ; 
 int /*<<< orphan*/  sc27xx_poweroff_do_poweroff ; 

__attribute__((used)) static int sc27xx_poweroff_probe(struct platform_device *pdev)
{
	if (regmap)
		return -EINVAL;

	regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!regmap)
		return -ENODEV;

	pm_power_off = sc27xx_poweroff_do_poweroff;
	register_syscore_ops(&poweroff_syscore_ops);
	return 0;
}