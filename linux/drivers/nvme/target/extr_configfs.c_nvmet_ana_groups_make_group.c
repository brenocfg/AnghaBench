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
typedef  int u32 ;
struct nvmet_port {int dummy; } ;
struct config_group {int /*<<< orphan*/  cg_item; } ;
struct nvmet_ana_group {int grpid; struct config_group group; struct nvmet_port* port; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct config_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVMET_MAX_ANAGRPS ; 
 struct nvmet_port* ana_groups_to_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 struct nvmet_ana_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvmet_ana_group_enabled ; 
 int /*<<< orphan*/  nvmet_ana_group_type ; 
 int /*<<< orphan*/  nvmet_ana_sem ; 
 int /*<<< orphan*/  nvmet_port_send_ana_event (struct nvmet_port*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct config_group *nvmet_ana_groups_make_group(
		struct config_group *group, const char *name)
{
	struct nvmet_port *port = ana_groups_to_port(&group->cg_item);
	struct nvmet_ana_group *grp;
	u32 grpid;
	int ret;

	ret = kstrtou32(name, 0, &grpid);
	if (ret)
		goto out;

	ret = -EINVAL;
	if (grpid <= 1 || grpid > NVMET_MAX_ANAGRPS)
		goto out;

	ret = -ENOMEM;
	grp = kzalloc(sizeof(*grp), GFP_KERNEL);
	if (!grp)
		goto out;
	grp->port = port;
	grp->grpid = grpid;

	down_write(&nvmet_ana_sem);
	nvmet_ana_group_enabled[grpid]++;
	up_write(&nvmet_ana_sem);

	nvmet_port_send_ana_event(grp->port);

	config_group_init_type_name(&grp->group, name, &nvmet_ana_group_type);
	return &grp->group;
out:
	return ERR_PTR(ret);
}