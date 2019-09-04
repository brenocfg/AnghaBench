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
 int ENODEV ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int pSeries_reconfig_remove_node (struct device_node*) ; 

__attribute__((used)) static int do_remove_node(char *buf)
{
	struct device_node *node;
	int rv = -ENODEV;

	if ((node = of_find_node_by_path(buf)))
		rv = pSeries_reconfig_remove_node(node);

	of_node_put(node);
	return rv;
}