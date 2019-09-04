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
struct device_node {int dummy; } ;
typedef  enum sensors { ____Placeholder_sensors } sensors ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int MAX_SENSOR_TYPE ; 
 char** legacy_compatibles ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 TYPE_1__* sensor_groups ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sensor_type(struct device_node *np)
{
	enum sensors type;
	const char *str;

	for (type = 0; type < ARRAY_SIZE(legacy_compatibles); type++) {
		if (of_device_is_compatible(np, legacy_compatibles[type]))
			return type;
	}

	/*
	 * Let's check if we have a newer device tree
	 */
	if (!of_device_is_compatible(np, "ibm,opal-sensor"))
		return MAX_SENSOR_TYPE;

	if (of_property_read_string(np, "sensor-type", &str))
		return MAX_SENSOR_TYPE;

	for (type = 0; type < MAX_SENSOR_TYPE; type++)
		if (!strcmp(str, sensor_groups[type].name))
			return type;

	return MAX_SENSOR_TYPE;
}