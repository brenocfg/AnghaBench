#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct of_reconfig_data {TYPE_1__* prop; int /*<<< orphan*/  dn; } ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  OF_RECONFIG_ATTACH_NODE 130 
#define  OF_RECONFIG_DETACH_NODE 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 int notifier_from_errno (int) ; 
 int pseries_add_mem_node (int /*<<< orphan*/ ) ; 
 int pseries_remove_mem_node (int /*<<< orphan*/ ) ; 
 int pseries_update_drconf_memory (struct of_reconfig_data*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pseries_memory_notifier(struct notifier_block *nb,
				   unsigned long action, void *data)
{
	struct of_reconfig_data *rd = data;
	int err = 0;

	switch (action) {
	case OF_RECONFIG_ATTACH_NODE:
		err = pseries_add_mem_node(rd->dn);
		break;
	case OF_RECONFIG_DETACH_NODE:
		err = pseries_remove_mem_node(rd->dn);
		break;
	case OF_RECONFIG_UPDATE_PROPERTY:
		if (!strcmp(rd->prop->name, "ibm,dynamic-memory"))
			err = pseries_update_drconf_memory(rd);
		break;
	}
	return notifier_from_errno(err);
}