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
struct fwnode_reference_args {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int fwnode_call_int_op (struct fwnode_handle const*,int /*<<< orphan*/ ,char const*,char const*,unsigned int,unsigned int,struct fwnode_reference_args*) ; 
 int /*<<< orphan*/  get_reference_args ; 

int fwnode_property_get_reference_args(const struct fwnode_handle *fwnode,
				       const char *prop, const char *nargs_prop,
				       unsigned int nargs, unsigned int index,
				       struct fwnode_reference_args *args)
{
	return fwnode_call_int_op(fwnode, get_reference_args, prop, nargs_prop,
				  nargs, index, args);
}