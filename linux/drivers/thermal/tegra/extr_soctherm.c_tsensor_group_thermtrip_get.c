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
struct tsensor_group_thermtrips {int id; int temp; } ;
struct tegra_soctherm {TYPE_1__* soc; } ;
struct TYPE_2__ {int num_ttgs; struct tsensor_group_thermtrips* thermtrips; } ;

/* Variables and functions */
 int TEGRA124_SOCTHERM_SENSOR_NUM ; 
 int min_low_temp ; 

__attribute__((used)) static int tsensor_group_thermtrip_get(struct tegra_soctherm *ts, int id)
{
	int i, temp = min_low_temp;
	struct tsensor_group_thermtrips *tt = ts->soc->thermtrips;

	if (id >= TEGRA124_SOCTHERM_SENSOR_NUM)
		return temp;

	if (tt) {
		for (i = 0; i < ts->soc->num_ttgs; i++) {
			if (tt[i].id == id)
				return tt[i].temp;
		}
	}

	return temp;
}