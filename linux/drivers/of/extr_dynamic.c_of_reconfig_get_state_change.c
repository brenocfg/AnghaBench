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
struct property {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct of_reconfig_data {struct property* old_prop; struct property* prop; int /*<<< orphan*/  dn; } ;

/* Variables and functions */
#define  OF_RECONFIG_ADD_PROPERTY 132 
#define  OF_RECONFIG_ATTACH_NODE 131 
 int OF_RECONFIG_CHANGE_ADD ; 
 int OF_RECONFIG_CHANGE_REMOVE ; 
#define  OF_RECONFIG_DETACH_NODE 130 
 int OF_RECONFIG_NO_CHANGE ; 
#define  OF_RECONFIG_REMOVE_PROPERTY 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 struct property* of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int of_reconfig_get_state_change(unsigned long action, struct of_reconfig_data *pr)
{
	struct property *prop, *old_prop = NULL;
	int is_status, status_state, old_status_state, prev_state, new_state;

	/* figure out if a device should be created or destroyed */
	switch (action) {
	case OF_RECONFIG_ATTACH_NODE:
	case OF_RECONFIG_DETACH_NODE:
		prop = of_find_property(pr->dn, "status", NULL);
		break;
	case OF_RECONFIG_ADD_PROPERTY:
	case OF_RECONFIG_REMOVE_PROPERTY:
		prop = pr->prop;
		break;
	case OF_RECONFIG_UPDATE_PROPERTY:
		prop = pr->prop;
		old_prop = pr->old_prop;
		break;
	default:
		return OF_RECONFIG_NO_CHANGE;
	}

	is_status = 0;
	status_state = -1;
	old_status_state = -1;
	prev_state = -1;
	new_state = -1;

	if (prop && !strcmp(prop->name, "status")) {
		is_status = 1;
		status_state = !strcmp(prop->value, "okay") ||
			       !strcmp(prop->value, "ok");
		if (old_prop)
			old_status_state = !strcmp(old_prop->value, "okay") ||
					   !strcmp(old_prop->value, "ok");
	}

	switch (action) {
	case OF_RECONFIG_ATTACH_NODE:
		prev_state = 0;
		/* -1 & 0 status either missing or okay */
		new_state = status_state != 0;
		break;
	case OF_RECONFIG_DETACH_NODE:
		/* -1 & 0 status either missing or okay */
		prev_state = status_state != 0;
		new_state = 0;
		break;
	case OF_RECONFIG_ADD_PROPERTY:
		if (is_status) {
			/* no status property -> enabled (legacy) */
			prev_state = 1;
			new_state = status_state;
		}
		break;
	case OF_RECONFIG_REMOVE_PROPERTY:
		if (is_status) {
			prev_state = status_state;
			/* no status property -> enabled (legacy) */
			new_state = 1;
		}
		break;
	case OF_RECONFIG_UPDATE_PROPERTY:
		if (is_status) {
			prev_state = old_status_state != 0;
			new_state = status_state != 0;
		}
		break;
	}

	if (prev_state == new_state)
		return OF_RECONFIG_NO_CHANGE;

	return new_state ? OF_RECONFIG_CHANGE_ADD : OF_RECONFIG_CHANGE_REMOVE;
}