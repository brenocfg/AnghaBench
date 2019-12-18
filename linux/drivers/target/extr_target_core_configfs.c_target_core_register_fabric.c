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
struct config_group {int /*<<< orphan*/  cg_item; } ;
struct target_fabric_configfs {char const tf_wwn_cit; char const tf_discovery_cit; struct config_group tf_group; struct config_group tf_disc_group; TYPE_1__* tf_ops; } ;
struct TYPE_2__ {char const* fabric_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,char const*) ; 
 char const* config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int request_module (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct target_fabric_configfs* target_core_get_fabric (char const*) ; 

__attribute__((used)) static struct config_group *target_core_register_fabric(
	struct config_group *group,
	const char *name)
{
	struct target_fabric_configfs *tf;
	int ret;

	pr_debug("Target_Core_ConfigFS: REGISTER -> group: %p name:"
			" %s\n", group, name);

	tf = target_core_get_fabric(name);
	if (!tf) {
		pr_debug("target_core_register_fabric() trying autoload for %s\n",
			 name);

		/*
		 * Below are some hardcoded request_module() calls to automatically
		 * local fabric modules when the following is called:
		 *
		 * mkdir -p /sys/kernel/config/target/$MODULE_NAME
		 *
		 * Note that this does not limit which TCM fabric module can be
		 * registered, but simply provids auto loading logic for modules with
		 * mkdir(2) system calls with known TCM fabric modules.
		 */

		if (!strncmp(name, "iscsi", 5)) {
			/*
			 * Automatically load the LIO Target fabric module when the
			 * following is called:
			 *
			 * mkdir -p $CONFIGFS/target/iscsi
			 */
			ret = request_module("iscsi_target_mod");
			if (ret < 0) {
				pr_debug("request_module() failed for"
				         " iscsi_target_mod.ko: %d\n", ret);
				return ERR_PTR(-EINVAL);
			}
		} else if (!strncmp(name, "loopback", 8)) {
			/*
			 * Automatically load the tcm_loop fabric module when the
			 * following is called:
			 *
			 * mkdir -p $CONFIGFS/target/loopback
			 */
			ret = request_module("tcm_loop");
			if (ret < 0) {
				pr_debug("request_module() failed for"
				         " tcm_loop.ko: %d\n", ret);
				return ERR_PTR(-EINVAL);
			}
		}

		tf = target_core_get_fabric(name);
	}

	if (!tf) {
		pr_debug("target_core_get_fabric() failed for %s\n",
		         name);
		return ERR_PTR(-EINVAL);
	}
	pr_debug("Target_Core_ConfigFS: REGISTER -> Located fabric:"
			" %s\n", tf->tf_ops->fabric_name);
	/*
	 * On a successful target_core_get_fabric() look, the returned
	 * struct target_fabric_configfs *tf will contain a usage reference.
	 */
	pr_debug("Target_Core_ConfigFS: REGISTER tfc_wwn_cit -> %p\n",
			&tf->tf_wwn_cit);

	config_group_init_type_name(&tf->tf_group, name, &tf->tf_wwn_cit);

	config_group_init_type_name(&tf->tf_disc_group, "discovery_auth",
			&tf->tf_discovery_cit);
	configfs_add_default_group(&tf->tf_disc_group, &tf->tf_group);

	pr_debug("Target_Core_ConfigFS: REGISTER -> Allocated Fabric: %s\n",
		 config_item_name(&tf->tf_group.cg_item));
	return &tf->tf_group;
}