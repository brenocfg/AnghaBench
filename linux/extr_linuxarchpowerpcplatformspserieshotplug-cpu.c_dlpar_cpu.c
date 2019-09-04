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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  drc_index; int /*<<< orphan*/  drc_count; } ;
struct pseries_hp_errorlog {int action; int /*<<< orphan*/  id_type; TYPE_1__ _drc_u; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PSERIES_HP_ELOG_ACTION_ADD 129 
#define  PSERIES_HP_ELOG_ACTION_REMOVE 128 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_COUNT ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_INDEX ; 
 int dlpar_cpu_add (int /*<<< orphan*/ ) ; 
 int dlpar_cpu_add_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_cpu_remove_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_cpu_remove_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

int dlpar_cpu(struct pseries_hp_errorlog *hp_elog)
{
	u32 count, drc_index;
	int rc;

	count = hp_elog->_drc_u.drc_count;
	drc_index = hp_elog->_drc_u.drc_index;

	lock_device_hotplug();

	switch (hp_elog->action) {
	case PSERIES_HP_ELOG_ACTION_REMOVE:
		if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT)
			rc = dlpar_cpu_remove_by_count(count);
		else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX)
			rc = dlpar_cpu_remove_by_index(drc_index);
		else
			rc = -EINVAL;
		break;
	case PSERIES_HP_ELOG_ACTION_ADD:
		if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT)
			rc = dlpar_cpu_add_by_count(count);
		else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX)
			rc = dlpar_cpu_add(drc_index);
		else
			rc = -EINVAL;
		break;
	default:
		pr_err("Invalid action (%d) specified\n", hp_elog->action);
		rc = -EINVAL;
		break;
	}

	unlock_device_hotplug();
	return rc;
}