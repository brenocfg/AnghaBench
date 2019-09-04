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
typedef  int /*<<< orphan*/  u32 ;
struct sensor_data {scalar_t__ opal_index; scalar_t__ type; int /*<<< orphan*/  hwmon_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwmon_index; } ;

/* Variables and functions */
 scalar_t__ INVALID_INDEX ; 
 TYPE_1__* sensor_groups ; 

__attribute__((used)) static u32 get_sensor_hwmon_index(struct sensor_data *sdata,
				  struct sensor_data *sdata_table, int count)
{
	int i;

	/*
	 * We don't use the OPAL index on newer device trees
	 */
	if (sdata->opal_index != INVALID_INDEX) {
		for (i = 0; i < count; i++)
			if (sdata_table[i].opal_index == sdata->opal_index &&
			    sdata_table[i].type == sdata->type)
				return sdata_table[i].hwmon_index;
	}
	return ++sensor_groups[sdata->type].hwmon_index;
}