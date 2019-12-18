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
struct sc27xx_fgu_data {int max_volt; } ;

/* Variables and functions */
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int sc27xx_fgu_get_vbat_vol (struct sc27xx_fgu_data*,int*) ; 

__attribute__((used)) static int sc27xx_fgu_get_health(struct sc27xx_fgu_data *data, int *health)
{
	int ret, vol;

	ret = sc27xx_fgu_get_vbat_vol(data, &vol);
	if (ret)
		return ret;

	if (vol > data->max_volt)
		*health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	else
		*health = POWER_SUPPLY_HEALTH_GOOD;

	return 0;
}