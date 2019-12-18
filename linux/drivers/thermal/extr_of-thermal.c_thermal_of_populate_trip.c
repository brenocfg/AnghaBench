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
struct thermal_trip {int temperature; int hysteresis; struct device_node* np; int /*<<< orphan*/  type; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int thermal_of_get_trip_type (struct device_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int thermal_of_populate_trip(struct device_node *np,
				    struct thermal_trip *trip)
{
	int prop;
	int ret;

	ret = of_property_read_u32(np, "temperature", &prop);
	if (ret < 0) {
		pr_err("missing temperature property\n");
		return ret;
	}
	trip->temperature = prop;

	ret = of_property_read_u32(np, "hysteresis", &prop);
	if (ret < 0) {
		pr_err("missing hysteresis property\n");
		return ret;
	}
	trip->hysteresis = prop;

	ret = thermal_of_get_trip_type(np, &trip->type);
	if (ret < 0) {
		pr_err("wrong trip type property\n");
		return ret;
	}

	/* Required for cooling map matching */
	trip->np = np;
	of_node_get(np);

	return 0;
}