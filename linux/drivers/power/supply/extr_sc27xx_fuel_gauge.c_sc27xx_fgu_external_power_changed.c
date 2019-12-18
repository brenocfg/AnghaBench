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
struct sc27xx_fgu_data {int /*<<< orphan*/  battery; } ;
struct power_supply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 struct sc27xx_fgu_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static void sc27xx_fgu_external_power_changed(struct power_supply *psy)
{
	struct sc27xx_fgu_data *data = power_supply_get_drvdata(psy);

	power_supply_changed(data->battery);
}