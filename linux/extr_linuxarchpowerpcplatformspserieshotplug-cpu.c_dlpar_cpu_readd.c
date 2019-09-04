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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int dlpar_cpu_add (int /*<<< orphan*/ ) ; 
 int dlpar_cpu_remove_by_index (int /*<<< orphan*/ ) ; 
 struct device* get_cpu_device (int) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

int dlpar_cpu_readd(int cpu)
{
	struct device_node *dn;
	struct device *dev;
	u32 drc_index;
	int rc;

	dev = get_cpu_device(cpu);
	dn = dev->of_node;

	rc = of_property_read_u32(dn, "ibm,my-drc-index", &drc_index);

	rc = dlpar_cpu_remove_by_index(drc_index);
	if (!rc)
		rc = dlpar_cpu_add(drc_index);

	return rc;
}