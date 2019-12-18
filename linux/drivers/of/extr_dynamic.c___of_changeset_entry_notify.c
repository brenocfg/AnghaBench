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
struct of_reconfig_data {int dn; } ;
struct of_changeset_entry {int action; int np; int /*<<< orphan*/  old_prop; int /*<<< orphan*/  prop; } ;
typedef  int /*<<< orphan*/  rd ;

/* Variables and functions */
 int EINVAL ; 
#define  OF_RECONFIG_ADD_PROPERTY 132 
#define  OF_RECONFIG_ATTACH_NODE 131 
#define  OF_RECONFIG_DETACH_NODE 130 
#define  OF_RECONFIG_REMOVE_PROPERTY 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 int /*<<< orphan*/  __of_changeset_entry_invert (struct of_changeset_entry*,struct of_changeset_entry*) ; 
 int /*<<< orphan*/  memset (struct of_reconfig_data*,int /*<<< orphan*/ ,int) ; 
 int of_property_notify (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_reconfig_notify (int,struct of_reconfig_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int __of_changeset_entry_notify(struct of_changeset_entry *ce,
		bool revert)
{
	struct of_reconfig_data rd;
	struct of_changeset_entry ce_inverted;
	int ret = 0;

	if (revert) {
		__of_changeset_entry_invert(ce, &ce_inverted);
		ce = &ce_inverted;
	}

	switch (ce->action) {
	case OF_RECONFIG_ATTACH_NODE:
	case OF_RECONFIG_DETACH_NODE:
		memset(&rd, 0, sizeof(rd));
		rd.dn = ce->np;
		ret = of_reconfig_notify(ce->action, &rd);
		break;
	case OF_RECONFIG_ADD_PROPERTY:
	case OF_RECONFIG_REMOVE_PROPERTY:
	case OF_RECONFIG_UPDATE_PROPERTY:
		ret = of_property_notify(ce->action, ce->np, ce->prop, ce->old_prop);
		break;
	default:
		pr_err("invalid devicetree changeset action: %i\n",
			(int)ce->action);
		ret = -EINVAL;
	}

	if (ret)
		pr_err("changeset notifier error @%pOF\n", ce->np);
	return ret;
}