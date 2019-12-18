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
struct fwnode_handle {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_count_strings (struct device_node const*,char const*) ; 
 int of_property_read_string_array (struct device_node const*,char const*,char const**,size_t) ; 
 struct device_node* to_of_node (struct fwnode_handle const*) ; 

__attribute__((used)) static int
of_fwnode_property_read_string_array(const struct fwnode_handle *fwnode,
				     const char *propname, const char **val,
				     size_t nval)
{
	const struct device_node *node = to_of_node(fwnode);

	return val ?
		of_property_read_string_array(node, propname, val, nval) :
		of_property_count_strings(node, propname);
}