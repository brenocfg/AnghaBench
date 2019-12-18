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
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int rpaphp_check_drc_props (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device_node *find_vio_slot_node(char *drc_name)
{
	struct device_node *parent = of_find_node_by_name(NULL, "vdevice");
	struct device_node *dn = NULL;
	int rc;

	if (!parent)
		return NULL;

	while ((dn = of_get_next_child(parent, dn))) {
		rc = rpaphp_check_drc_props(dn, drc_name, NULL);
		if (rc == 0)
			break;
	}
	of_node_put(parent);

	return dn;
}