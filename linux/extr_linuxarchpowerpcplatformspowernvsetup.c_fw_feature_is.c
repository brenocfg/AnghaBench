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
 struct device_node* of_get_child_by_name (struct device_node*,char const*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_bool (struct device_node*,char const*) ; 

__attribute__((used)) static bool fw_feature_is(const char *state, const char *name,
			  struct device_node *fw_features)
{
	struct device_node *np;
	bool rc = false;

	np = of_get_child_by_name(fw_features, name);
	if (np) {
		rc = of_property_read_bool(np, state);
		of_node_put(np);
	}

	return rc;
}