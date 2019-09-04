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

/* Variables and functions */
 int /*<<< orphan*/  pset_prop_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  to_pset_node (struct fwnode_handle const*) ; 

__attribute__((used)) static bool pset_fwnode_property_present(const struct fwnode_handle *fwnode,
					 const char *propname)
{
	return !!pset_prop_get(to_pset_node(fwnode), propname);
}