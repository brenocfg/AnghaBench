#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  drc_index; TYPE_1__ ic; int /*<<< orphan*/  drc_count; } ;
struct pseries_hp_errorlog {int action; TYPE_2__ _drc_u; int /*<<< orphan*/  id_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PSERIES_HP_ELOG_ACTION_ADD 130 
#define  PSERIES_HP_ELOG_ACTION_READD 129 
#define  PSERIES_HP_ELOG_ACTION_REMOVE 128 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_COUNT ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_IC ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_INDEX ; 
 int dlpar_memory_add_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_memory_add_by_ic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlpar_memory_add_by_index (int /*<<< orphan*/ ) ; 
 int dlpar_memory_readd_by_index (int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_count (int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_ic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlpar_memory_remove_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

int dlpar_memory(struct pseries_hp_errorlog *hp_elog)
{
	u32 count, drc_index;
	int rc;

	lock_device_hotplug();

	switch (hp_elog->action) {
	case PSERIES_HP_ELOG_ACTION_ADD:
		if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT) {
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_add_by_count(count);
		} else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX) {
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_add_by_index(drc_index);
		} else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_IC) {
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_add_by_ic(count, drc_index);
		} else {
			rc = -EINVAL;
		}

		break;
	case PSERIES_HP_ELOG_ACTION_REMOVE:
		if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT) {
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_remove_by_count(count);
		} else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX) {
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_remove_by_index(drc_index);
		} else if (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_IC) {
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_remove_by_ic(count, drc_index);
		} else {
			rc = -EINVAL;
		}

		break;
	case PSERIES_HP_ELOG_ACTION_READD:
		drc_index = hp_elog->_drc_u.drc_index;
		rc = dlpar_memory_readd_by_index(drc_index);
		break;
	default:
		pr_err("Invalid action (%d) specified\n", hp_elog->action);
		rc = -EINVAL;
		break;
	}

	unlock_device_hotplug();
	return rc;
}