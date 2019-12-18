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
typedef  int /*<<< orphan*/  u64 ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; } ;
struct se_lun_acl {struct se_node_acl* se_lun_nacl; int /*<<< orphan*/  mapped_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TRANSPORT_IQN_LEN ; 
 struct se_lun_acl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

struct se_lun_acl *core_dev_init_initiator_node_lun_acl(
	struct se_portal_group *tpg,
	struct se_node_acl *nacl,
	u64 mapped_lun,
	int *ret)
{
	struct se_lun_acl *lacl;

	if (strlen(nacl->initiatorname) >= TRANSPORT_IQN_LEN) {
		pr_err("%s InitiatorName exceeds maximum size.\n",
			tpg->se_tpg_tfo->fabric_name);
		*ret = -EOVERFLOW;
		return NULL;
	}
	lacl = kzalloc(sizeof(struct se_lun_acl), GFP_KERNEL);
	if (!lacl) {
		pr_err("Unable to allocate memory for struct se_lun_acl.\n");
		*ret = -ENOMEM;
		return NULL;
	}

	lacl->mapped_lun = mapped_lun;
	lacl->se_lun_nacl = nacl;

	return lacl;
}