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
struct twl4030_vibra_data {scalar_t__ coexist; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool twl4030_vibra_check_coexist(struct twl4030_vibra_data *pdata,
			      struct device_node *parent)
{
	struct device_node *node;

	if (pdata && pdata->coexist)
		return true;

	node = of_get_child_by_name(parent, "codec");
	if (node) {
		of_node_put(node);
		return true;
	}

	return false;
}