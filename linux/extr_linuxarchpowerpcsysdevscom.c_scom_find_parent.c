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
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/  const) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

struct device_node *scom_find_parent(struct device_node *node)
{
	struct device_node *par, *tmp;
	const u32 *p;

	for (par = of_node_get(node); par;) {
		if (of_get_property(par, "scom-controller", NULL))
			break;
		p = of_get_property(par, "scom-parent", NULL);
		tmp = par;
		if (p == NULL)
			par = of_get_parent(par);
		else
			par = of_find_node_by_phandle(*p);
		of_node_put(tmp);
	}
	return par;
}