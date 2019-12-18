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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct config_group {int dummy; } ;
struct TYPE_4__ {int grpid; struct config_group group; struct nvmet_port* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  treq; int /*<<< orphan*/  portid; } ;
struct nvmet_port {int inline_data_size; struct config_group group; struct config_group ana_groups_group; TYPE_2__ ana_default_group; struct config_group referrals_group; struct config_group subsys_group; TYPE_1__ disc_addr; int /*<<< orphan*/  referrals; int /*<<< orphan*/  subsystems; int /*<<< orphan*/  entry; int /*<<< orphan*/  global_entry; int /*<<< orphan*/ * ana_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NVMET_DEFAULT_ANA_GRPID ; 
 int NVMET_MAX_ANAGRPS ; 
 int /*<<< orphan*/  NVME_ANA_INACCESSIBLE ; 
 int /*<<< orphan*/  NVME_ANA_OPTIMIZED ; 
 int /*<<< orphan*/  NVMF_TREQ_DISABLE_SQFLOW ; 
 char* __stringify (int) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmet_port*) ; 
 scalar_t__ kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvmet_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_ana_group_type ; 
 int /*<<< orphan*/  nvmet_ana_groups_type ; 
 int /*<<< orphan*/  nvmet_port_subsys_type ; 
 int /*<<< orphan*/  nvmet_port_type ; 
 int /*<<< orphan*/  nvmet_ports_list ; 
 int /*<<< orphan*/  nvmet_referrals_type ; 

__attribute__((used)) static struct config_group *nvmet_ports_make(struct config_group *group,
		const char *name)
{
	struct nvmet_port *port;
	u16 portid;
	u32 i;

	if (kstrtou16(name, 0, &portid))
		return ERR_PTR(-EINVAL);

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return ERR_PTR(-ENOMEM);

	port->ana_state = kcalloc(NVMET_MAX_ANAGRPS + 1,
			sizeof(*port->ana_state), GFP_KERNEL);
	if (!port->ana_state) {
		kfree(port);
		return ERR_PTR(-ENOMEM);
	}

	for (i = 1; i <= NVMET_MAX_ANAGRPS; i++) {
		if (i == NVMET_DEFAULT_ANA_GRPID)
			port->ana_state[1] = NVME_ANA_OPTIMIZED;
		else
			port->ana_state[i] = NVME_ANA_INACCESSIBLE;
	}

	list_add(&port->global_entry, &nvmet_ports_list);

	INIT_LIST_HEAD(&port->entry);
	INIT_LIST_HEAD(&port->subsystems);
	INIT_LIST_HEAD(&port->referrals);
	port->inline_data_size = -1;	/* < 0 == let the transport choose */

	port->disc_addr.portid = cpu_to_le16(portid);
	port->disc_addr.treq = NVMF_TREQ_DISABLE_SQFLOW;
	config_group_init_type_name(&port->group, name, &nvmet_port_type);

	config_group_init_type_name(&port->subsys_group,
			"subsystems", &nvmet_port_subsys_type);
	configfs_add_default_group(&port->subsys_group, &port->group);

	config_group_init_type_name(&port->referrals_group,
			"referrals", &nvmet_referrals_type);
	configfs_add_default_group(&port->referrals_group, &port->group);

	config_group_init_type_name(&port->ana_groups_group,
			"ana_groups", &nvmet_ana_groups_type);
	configfs_add_default_group(&port->ana_groups_group, &port->group);

	port->ana_default_group.port = port;
	port->ana_default_group.grpid = NVMET_DEFAULT_ANA_GRPID;
	config_group_init_type_name(&port->ana_default_group.group,
			__stringify(NVMET_DEFAULT_ANA_GRPID),
			&nvmet_ana_group_type);
	configfs_add_default_group(&port->ana_default_group.group,
			&port->ana_groups_group);

	return &port->group;
}