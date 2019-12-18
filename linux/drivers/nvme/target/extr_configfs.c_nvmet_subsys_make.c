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
struct nvmet_subsys {struct config_group group; struct config_group allowed_hosts_group; struct config_group namespaces_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct config_group* ERR_CAST (struct nvmet_subsys*) ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct nvmet_subsys*) ; 
 int /*<<< orphan*/  NVME_DISC_SUBSYS_NAME ; 
 int /*<<< orphan*/  NVME_NQN_NVME ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  nvmet_allowed_hosts_type ; 
 int /*<<< orphan*/  nvmet_namespaces_type ; 
 struct nvmet_subsys* nvmet_subsys_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_subsys_type ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct config_group *nvmet_subsys_make(struct config_group *group,
		const char *name)
{
	struct nvmet_subsys *subsys;

	if (sysfs_streq(name, NVME_DISC_SUBSYS_NAME)) {
		pr_err("can't create discovery subsystem through configfs\n");
		return ERR_PTR(-EINVAL);
	}

	subsys = nvmet_subsys_alloc(name, NVME_NQN_NVME);
	if (IS_ERR(subsys))
		return ERR_CAST(subsys);

	config_group_init_type_name(&subsys->group, name, &nvmet_subsys_type);

	config_group_init_type_name(&subsys->namespaces_group,
			"namespaces", &nvmet_namespaces_type);
	configfs_add_default_group(&subsys->namespaces_group, &subsys->group);

	config_group_init_type_name(&subsys->allowed_hosts_group,
			"allowed_hosts", &nvmet_allowed_hosts_type);
	configfs_add_default_group(&subsys->allowed_hosts_group,
			&subsys->group);

	return &subsys->group;
}