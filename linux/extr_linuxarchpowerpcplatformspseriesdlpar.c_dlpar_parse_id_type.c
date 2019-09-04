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
struct TYPE_3__ {void* index; void* count; } ;
struct TYPE_4__ {void* drc_count; void* drc_index; TYPE_1__ ic; } ;
struct pseries_hp_errorlog {TYPE_2__ _drc_u; int /*<<< orphan*/  id_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_COUNT ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_IC ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_ID_DRC_INDEX ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ sysfs_streq (char*,char*) ; 

__attribute__((used)) static int dlpar_parse_id_type(char **cmd, struct pseries_hp_errorlog *hp_elog)
{
	char *arg;
	u32 count, index;

	arg = strsep(cmd, " ");
	if (!arg)
		return -EINVAL;

	if (sysfs_streq(arg, "indexed-count")) {
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_IC;
		arg = strsep(cmd, " ");
		if (!arg) {
			pr_err("No DRC count specified.\n");
			return -EINVAL;
		}

		if (kstrtou32(arg, 0, &count)) {
			pr_err("Invalid DRC count specified.\n");
			return -EINVAL;
		}

		arg = strsep(cmd, " ");
		if (!arg) {
			pr_err("No DRC Index specified.\n");
			return -EINVAL;
		}

		if (kstrtou32(arg, 0, &index)) {
			pr_err("Invalid DRC Index specified.\n");
			return -EINVAL;
		}

		hp_elog->_drc_u.ic.count = cpu_to_be32(count);
		hp_elog->_drc_u.ic.index = cpu_to_be32(index);
	} else if (sysfs_streq(arg, "index")) {
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_INDEX;
		arg = strsep(cmd, " ");
		if (!arg) {
			pr_err("No DRC Index specified.\n");
			return -EINVAL;
		}

		if (kstrtou32(arg, 0, &index)) {
			pr_err("Invalid DRC Index specified.\n");
			return -EINVAL;
		}

		hp_elog->_drc_u.drc_index = cpu_to_be32(index);
	} else if (sysfs_streq(arg, "count")) {
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_COUNT;
		arg = strsep(cmd, " ");
		if (!arg) {
			pr_err("No DRC count specified.\n");
			return -EINVAL;
		}

		if (kstrtou32(arg, 0, &count)) {
			pr_err("Invalid DRC count specified.\n");
			return -EINVAL;
		}

		hp_elog->_drc_u.drc_count = cpu_to_be32(count);
	} else {
		pr_err("Invalid id_type specified.\n");
		return -EINVAL;
	}

	return 0;
}