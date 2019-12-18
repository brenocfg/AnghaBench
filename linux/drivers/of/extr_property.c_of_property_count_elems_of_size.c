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
struct property {int length; int /*<<< orphan*/  value; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 struct property* of_find_property (struct device_node const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,struct device_node const*,int) ; 

int of_property_count_elems_of_size(const struct device_node *np,
				const char *propname, int elem_size)
{
	struct property *prop = of_find_property(np, propname, NULL);

	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;

	if (prop->length % elem_size != 0) {
		pr_err("size of %s in node %pOF is not a multiple of %d\n",
		       propname, np, elem_size);
		return -EINVAL;
	}

	return prop->length / elem_size;
}