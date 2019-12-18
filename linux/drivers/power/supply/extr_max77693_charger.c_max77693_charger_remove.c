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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct max77693_charger {int /*<<< orphan*/  charger; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_fast_charge_timer ; 
 int /*<<< orphan*/  dev_attr_top_off_threshold_current ; 
 int /*<<< orphan*/  dev_attr_top_off_timer ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct max77693_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77693_charger_remove(struct platform_device *pdev)
{
	struct max77693_charger *chg = platform_get_drvdata(pdev);

	device_remove_file(&pdev->dev, &dev_attr_top_off_timer);
	device_remove_file(&pdev->dev, &dev_attr_top_off_threshold_current);
	device_remove_file(&pdev->dev, &dev_attr_fast_charge_timer);

	power_supply_unregister(chg->charger);

	return 0;
}