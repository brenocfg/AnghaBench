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
struct se_portal_group {int /*<<< orphan*/  acl_node_mutex; } ;
struct se_node_acl {int /*<<< orphan*/  acl_kref; } ;

/* Variables and functions */
 struct se_node_acl* __core_tpg_get_initiator_node_acl (struct se_portal_group*,unsigned char*) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct se_node_acl *core_tpg_get_initiator_node_acl(
	struct se_portal_group *tpg,
	unsigned char *initiatorname)
{
	struct se_node_acl *acl;
	/*
	 * Obtain se_node_acl->acl_kref using fabric driver provided
	 * initiatorname[] during node acl endpoint lookup driven by
	 * new se_session login.
	 *
	 * The reference is held until se_session shutdown -> release
	 * occurs via fabric driver invoked transport_deregister_session()
	 * or transport_free_session() code.
	 */
	mutex_lock(&tpg->acl_node_mutex);
	acl = __core_tpg_get_initiator_node_acl(tpg, initiatorname);
	if (acl) {
		if (!kref_get_unless_zero(&acl->acl_kref))
			acl = NULL;
	}
	mutex_unlock(&tpg->acl_node_mutex);

	return acl;
}