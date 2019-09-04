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

/* Variables and functions */
 int ENODEV ; 
 struct device_node* cpu_drc_index_to_dn (int /*<<< orphan*/ ) ; 
 int dlpar_cpu_remove (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlpar_cpu_remove_by_index(u32 drc_index)
{
	struct device_node *dn;
	int rc;

	dn = cpu_drc_index_to_dn(drc_index);
	if (!dn) {
		pr_warn("Cannot find CPU (drc index %x) to remove\n",
			drc_index);
		return -ENODEV;
	}

	rc = dlpar_cpu_remove(dn, drc_index);
	of_node_put(dn);
	return rc;
}