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
typedef  int u32 ;
struct sensor_data {int /*<<< orphan*/  label; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int get_logical_cpu (int) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 size_t snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static void make_sensor_label(struct device_node *np,
			      struct sensor_data *sdata, const char *label)
{
	u32 id;
	size_t n;

	n = snprintf(sdata->label, sizeof(sdata->label), "%s", label);

	/*
	 * Core temp pretty print
	 */
	if (!of_property_read_u32(np, "ibm,pir", &id)) {
		int cpuid = get_logical_cpu(id);

		if (cpuid >= 0)
			/*
			 * The digital thermal sensors are associated
			 * with a core.
			 */
			n += snprintf(sdata->label + n,
				      sizeof(sdata->label) - n, " %d",
				      cpuid);
		else
			n += snprintf(sdata->label + n,
				      sizeof(sdata->label) - n, " phy%d", id);
	}

	/*
	 * Membuffer pretty print
	 */
	if (!of_property_read_u32(np, "ibm,chip-id", &id))
		n += snprintf(sdata->label + n, sizeof(sdata->label) - n,
			      " %d", id & 0xffff);
}