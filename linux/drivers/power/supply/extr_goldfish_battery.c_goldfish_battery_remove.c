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
struct goldfish_battery_data {int /*<<< orphan*/  ac; int /*<<< orphan*/  battery; } ;

/* Variables and functions */
 struct goldfish_battery_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goldfish_battery_remove(struct platform_device *pdev)
{
	struct goldfish_battery_data *data = platform_get_drvdata(pdev);

	power_supply_unregister(data->battery);
	power_supply_unregister(data->ac);
	return 0;
}