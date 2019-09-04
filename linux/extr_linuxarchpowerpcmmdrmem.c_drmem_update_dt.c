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
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int drmem_update_dt_v1 (struct device_node*,struct property*) ; 
 int drmem_update_dt_v2 (struct device_node*,struct property*) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int drmem_update_dt(void)
{
	struct device_node *memory;
	struct property *prop;
	int rc = -1;

	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	if (!memory)
		return -1;

	prop = of_find_property(memory, "ibm,dynamic-memory", NULL);
	if (prop) {
		rc = drmem_update_dt_v1(memory, prop);
	} else {
		prop = of_find_property(memory, "ibm,dynamic-memory-v2", NULL);
		if (prop)
			rc = drmem_update_dt_v2(memory, prop);
	}

	of_node_put(memory);
	return rc;
}