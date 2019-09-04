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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_detach_node (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int dlpar_detach_node(struct device_node *dn)
{
	struct device_node *child;
	int rc;

	child = of_get_next_child(dn, NULL);
	while (child) {
		dlpar_detach_node(child);
		child = of_get_next_child(dn, child);
	}

	rc = of_detach_node(dn);
	if (rc)
		return rc;

	of_node_put(dn);

	return 0;
}