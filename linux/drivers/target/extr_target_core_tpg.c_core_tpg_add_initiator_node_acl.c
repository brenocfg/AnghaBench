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
struct se_portal_group {int /*<<< orphan*/  acl_node_mutex; TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {scalar_t__ dynamic_node_acl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct se_node_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct se_node_acl* __core_tpg_get_initiator_node_acl (struct se_portal_group*,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  target_add_node_acl (struct se_node_acl*) ; 
 struct se_node_acl* target_alloc_node_acl (struct se_portal_group*,char const*) ; 

struct se_node_acl *core_tpg_add_initiator_node_acl(
	struct se_portal_group *tpg,
	const char *initiatorname)
{
	struct se_node_acl *acl;

	mutex_lock(&tpg->acl_node_mutex);
	acl = __core_tpg_get_initiator_node_acl(tpg, initiatorname);
	if (acl) {
		if (acl->dynamic_node_acl) {
			acl->dynamic_node_acl = 0;
			pr_debug("%s_TPG[%u] - Replacing dynamic ACL"
				" for %s\n", tpg->se_tpg_tfo->fabric_name,
				tpg->se_tpg_tfo->tpg_get_tag(tpg), initiatorname);
			mutex_unlock(&tpg->acl_node_mutex);
			return acl;
		}

		pr_err("ACL entry for %s Initiator"
			" Node %s already exists for TPG %u, ignoring"
			" request.\n",  tpg->se_tpg_tfo->fabric_name,
			initiatorname, tpg->se_tpg_tfo->tpg_get_tag(tpg));
		mutex_unlock(&tpg->acl_node_mutex);
		return ERR_PTR(-EEXIST);
	}
	mutex_unlock(&tpg->acl_node_mutex);

	acl = target_alloc_node_acl(tpg, initiatorname);
	if (!acl)
		return ERR_PTR(-ENOMEM);

	target_add_node_acl(acl);
	return acl;
}