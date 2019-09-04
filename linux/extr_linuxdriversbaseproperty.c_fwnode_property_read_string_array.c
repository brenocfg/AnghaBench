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
struct fwnode_handle {struct fwnode_handle const* secondary; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct fwnode_handle const*) ; 
 int fwnode_call_int_op (struct fwnode_handle const*,int /*<<< orphan*/ ,char const*,char const**,size_t) ; 
 int /*<<< orphan*/  property_read_string_array ; 

int fwnode_property_read_string_array(const struct fwnode_handle *fwnode,
				      const char *propname, const char **val,
				      size_t nval)
{
	int ret;

	ret = fwnode_call_int_op(fwnode, property_read_string_array, propname,
				 val, nval);
	if (ret == -EINVAL && !IS_ERR_OR_NULL(fwnode) &&
	    !IS_ERR_OR_NULL(fwnode->secondary))
		ret = fwnode_call_int_op(fwnode->secondary,
					 property_read_string_array, propname,
					 val, nval);
	return ret;
}