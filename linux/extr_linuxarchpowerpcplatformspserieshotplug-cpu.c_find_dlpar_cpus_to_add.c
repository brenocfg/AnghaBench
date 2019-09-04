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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ dlpar_cpu_exists (struct device_node*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int find_dlpar_cpus_to_add(u32 *cpu_drcs, u32 cpus_to_add)
{
	struct device_node *parent;
	int cpus_found = 0;
	int index, rc;

	parent = of_find_node_by_path("/cpus");
	if (!parent) {
		pr_warn("Could not find CPU root node in device tree\n");
		kfree(cpu_drcs);
		return -1;
	}

	/* Search the ibm,drc-indexes array for possible CPU drcs to
	 * add. Note that the format of the ibm,drc-indexes array is
	 * the number of entries in the array followed by the array
	 * of drc values so we start looking at index = 1.
	 */
	index = 1;
	while (cpus_found < cpus_to_add) {
		u32 drc;

		rc = of_property_read_u32_index(parent, "ibm,drc-indexes",
						index++, &drc);
		if (rc)
			break;

		if (dlpar_cpu_exists(parent, drc))
			continue;

		cpu_drcs[cpus_found++] = drc;
	}

	of_node_put(parent);
	return cpus_found;
}