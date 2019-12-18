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
struct max8925_power_info {int /*<<< orphan*/  battery; int /*<<< orphan*/  usb; int /*<<< orphan*/  ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  max8925_deinit_charger (struct max8925_power_info*) ; 
 struct max8925_power_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8925_power_remove(struct platform_device *pdev)
{
	struct max8925_power_info *info = platform_get_drvdata(pdev);

	if (info) {
		power_supply_unregister(info->ac);
		power_supply_unregister(info->usb);
		power_supply_unregister(info->battery);
		max8925_deinit_charger(info);
	}
	return 0;
}