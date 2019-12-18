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
struct pmbus_sensor {int page; int reg; struct pmbus_sensor* next; } ;
struct pmbus_data {struct pmbus_sensor* sensors; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct pmbus_sensor* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pmbus_sensor *pmbus_find_sensor(struct pmbus_data *data, int page,
					      int reg)
{
	struct pmbus_sensor *sensor;

	for (sensor = data->sensors; sensor; sensor = sensor->next) {
		if (sensor->page == page && sensor->reg == reg)
			return sensor;
	}

	return ERR_PTR(-EINVAL);
}