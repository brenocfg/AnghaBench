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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  OF_RECONFIG_ADD_PROPERTY 132 
#define  OF_RECONFIG_ATTACH_NODE 131 
#define  OF_RECONFIG_DETACH_NODE 130 
#define  OF_RECONFIG_REMOVE_PROPERTY 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 int /*<<< orphan*/ * action_names ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct of_reconfig_data*) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/  of_reconfig_chain ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int of_reconfig_notify(unsigned long action, struct of_reconfig_data *p)
{
	int rc;
#ifdef DEBUG
	struct of_reconfig_data *pr = p;

	switch (action) {
	case OF_RECONFIG_ATTACH_NODE:
	case OF_RECONFIG_DETACH_NODE:
		pr_debug("notify %-15s %pOF\n", action_names[action],
			pr->dn);
		break;
	case OF_RECONFIG_ADD_PROPERTY:
	case OF_RECONFIG_REMOVE_PROPERTY:
	case OF_RECONFIG_UPDATE_PROPERTY:
		pr_debug("notify %-15s %pOF:%s\n", action_names[action],
			pr->dn, pr->prop->name);
		break;

	}
#endif
	rc = blocking_notifier_call_chain(&of_reconfig_chain, action, p);
	return notifier_to_errno(rc);
}