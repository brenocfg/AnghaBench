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
struct pseries_hp_errorlog {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_RESOURCE_CPU ; 
 int /*<<< orphan*/  PSERIES_HP_ELOG_RESOURCE_MEM ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ sysfs_streq (char*,char*) ; 

__attribute__((used)) static int dlpar_parse_resource(char **cmd, struct pseries_hp_errorlog *hp_elog)
{
	char *arg;

	arg = strsep(cmd, " ");
	if (!arg)
		return -EINVAL;

	if (sysfs_streq(arg, "memory")) {
		hp_elog->resource = PSERIES_HP_ELOG_RESOURCE_MEM;
	} else if (sysfs_streq(arg, "cpu")) {
		hp_elog->resource = PSERIES_HP_ELOG_RESOURCE_CPU;
	} else {
		pr_err("Invalid resource specified.\n");
		return -EINVAL;
	}

	return 0;
}