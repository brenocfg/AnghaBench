#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct target {TYPE_1__* np; scalar_t__ in_livetree; } ;
struct property {struct property* value; struct property* name; struct property* next; } ;
struct overlay_changeset {int /*<<< orphan*/  cset; } ;
struct TYPE_6__ {struct property* deadprops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OF_OVERLAY ; 
 struct property* __of_prop_dup (struct property*,int /*<<< orphan*/ ) ; 
 struct property* dup_and_fixup_symbol_prop (struct overlay_changeset*,struct property*) ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 int of_changeset_add_property (int /*<<< orphan*/ *,TYPE_1__*,struct property*) ; 
 int of_changeset_update_property (int /*<<< orphan*/ *,TYPE_1__*,struct property*) ; 
 struct property* of_find_property (TYPE_1__*,struct property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_check_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_prop_cmp (struct property*,char*) ; 
 int /*<<< orphan*/  of_prop_val_eq (struct property*,struct property*) ; 
 int /*<<< orphan*/  pr_err (char*,TYPE_1__*,...) ; 

__attribute__((used)) static int add_changeset_property(struct overlay_changeset *ovcs,
		struct target *target, struct property *overlay_prop,
		bool is_symbols_prop)
{
	struct property *new_prop = NULL, *prop;
	int ret = 0;
	bool check_for_non_overlay_node = false;

	if (target->in_livetree)
		if (!of_prop_cmp(overlay_prop->name, "name") ||
		    !of_prop_cmp(overlay_prop->name, "phandle") ||
		    !of_prop_cmp(overlay_prop->name, "linux,phandle"))
			return 0;

	if (target->in_livetree)
		prop = of_find_property(target->np, overlay_prop->name, NULL);
	else
		prop = NULL;

	if (is_symbols_prop) {
		if (prop)
			return -EINVAL;
		new_prop = dup_and_fixup_symbol_prop(ovcs, overlay_prop);
	} else {
		new_prop = __of_prop_dup(overlay_prop, GFP_KERNEL);
	}

	if (!new_prop)
		return -ENOMEM;

	if (!prop) {
		check_for_non_overlay_node = true;
		if (!target->in_livetree) {
			new_prop->next = target->np->deadprops;
			target->np->deadprops = new_prop;
		}
		ret = of_changeset_add_property(&ovcs->cset, target->np,
						new_prop);
	} else if (!of_prop_cmp(prop->name, "#address-cells")) {
		if (!of_prop_val_eq(prop, new_prop)) {
			pr_err("ERROR: changing value of #address-cells is not allowed in %pOF\n",
			       target->np);
			ret = -EINVAL;
		}
	} else if (!of_prop_cmp(prop->name, "#size-cells")) {
		if (!of_prop_val_eq(prop, new_prop)) {
			pr_err("ERROR: changing value of #size-cells is not allowed in %pOF\n",
			       target->np);
			ret = -EINVAL;
		}
	} else {
		check_for_non_overlay_node = true;
		ret = of_changeset_update_property(&ovcs->cset, target->np,
						   new_prop);
	}

	if (check_for_non_overlay_node &&
	    !of_node_check_flag(target->np, OF_OVERLAY))
		pr_err("WARNING: memory leak will occur if overlay removed, property: %pOF/%s\n",
		       target->np, new_prop->name);

	if (ret) {
		kfree(new_prop->name);
		kfree(new_prop->value);
		kfree(new_prop);
	}
	return ret;
}