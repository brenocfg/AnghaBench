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
struct config_group {int dummy; } ;
struct se_hba {struct config_group hba_group; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 struct config_group* ERR_CAST (struct se_hba*) ; 
 struct config_group* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct se_hba*) ; 
 int TARGET_CORE_NAME_MAX_LEN ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 struct se_hba* core_alloc_hba (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  target_core_hba_cit ; 
 int /*<<< orphan*/  transport_subsystem_check_init () ; 

__attribute__((used)) static struct config_group *target_core_call_addhbatotarget(
	struct config_group *group,
	const char *name)
{
	char *se_plugin_str, *str, *str2;
	struct se_hba *hba;
	char buf[TARGET_CORE_NAME_MAX_LEN];
	unsigned long plugin_dep_id = 0;
	int ret;

	memset(buf, 0, TARGET_CORE_NAME_MAX_LEN);
	if (strlen(name) >= TARGET_CORE_NAME_MAX_LEN) {
		pr_err("Passed *name strlen(): %d exceeds"
			" TARGET_CORE_NAME_MAX_LEN: %d\n", (int)strlen(name),
			TARGET_CORE_NAME_MAX_LEN);
		return ERR_PTR(-ENAMETOOLONG);
	}
	snprintf(buf, TARGET_CORE_NAME_MAX_LEN, "%s", name);

	str = strstr(buf, "_");
	if (!str) {
		pr_err("Unable to locate \"_\" for $SUBSYSTEM_PLUGIN_$HOST_ID\n");
		return ERR_PTR(-EINVAL);
	}
	se_plugin_str = buf;
	/*
	 * Special case for subsystem plugins that have "_" in their names.
	 * Namely rd_direct and rd_mcp..
	 */
	str2 = strstr(str+1, "_");
	if (str2) {
		*str2 = '\0'; /* Terminate for *se_plugin_str */
		str2++; /* Skip to start of plugin dependent ID */
		str = str2;
	} else {
		*str = '\0'; /* Terminate for *se_plugin_str */
		str++; /* Skip to start of plugin dependent ID */
	}

	ret = kstrtoul(str, 0, &plugin_dep_id);
	if (ret < 0) {
		pr_err("kstrtoul() returned %d for"
				" plugin_dep_id\n", ret);
		return ERR_PTR(ret);
	}
	/*
	 * Load up TCM subsystem plugins if they have not already been loaded.
	 */
	transport_subsystem_check_init();

	hba = core_alloc_hba(se_plugin_str, plugin_dep_id, 0);
	if (IS_ERR(hba))
		return ERR_CAST(hba);

	config_group_init_type_name(&hba->hba_group, name,
			&target_core_hba_cit);

	return &hba->hba_group;
}