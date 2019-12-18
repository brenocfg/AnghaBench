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
struct target_core_fabric_ops {int /*<<< orphan*/  fabric_name; int /*<<< orphan*/  (* sess_get_initiator_sid ) (struct se_session*,unsigned char*,int) ;int /*<<< orphan*/  (* tpg_check_prot_fabric_only ) (struct se_portal_group*) ;} ;
struct se_session {void* fabric_sess_ptr; int /*<<< orphan*/  sess_list; int /*<<< orphan*/  sess_acl_list; int /*<<< orphan*/  sess_bin_isid; int /*<<< orphan*/  sess_prot_type; struct se_portal_group* se_tpg; } ;
struct se_portal_group {struct target_core_fabric_ops* se_tpg_tfo; int /*<<< orphan*/  tpg_sess_list; } ;
struct se_node_acl {int /*<<< orphan*/  nacl_sess_lock; int /*<<< orphan*/  acl_sess_list; struct se_session* nacl_sess; int /*<<< orphan*/  saved_prot_type; } ;

/* Variables and functions */
 int PR_REG_ISID_LEN ; 
 int /*<<< orphan*/  get_unaligned_be64 (unsigned char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_session*,unsigned char*,int) ; 

void __transport_register_session(
	struct se_portal_group *se_tpg,
	struct se_node_acl *se_nacl,
	struct se_session *se_sess,
	void *fabric_sess_ptr)
{
	const struct target_core_fabric_ops *tfo = se_tpg->se_tpg_tfo;
	unsigned char buf[PR_REG_ISID_LEN];
	unsigned long flags;

	se_sess->se_tpg = se_tpg;
	se_sess->fabric_sess_ptr = fabric_sess_ptr;
	/*
	 * Used by struct se_node_acl's under ConfigFS to locate active se_session-t
	 *
	 * Only set for struct se_session's that will actually be moving I/O.
	 * eg: *NOT* discovery sessions.
	 */
	if (se_nacl) {
		/*
		 *
		 * Determine if fabric allows for T10-PI feature bits exposed to
		 * initiators for device backends with !dev->dev_attrib.pi_prot_type.
		 *
		 * If so, then always save prot_type on a per se_node_acl node
		 * basis and re-instate the previous sess_prot_type to avoid
		 * disabling PI from below any previously initiator side
		 * registered LUNs.
		 */
		if (se_nacl->saved_prot_type)
			se_sess->sess_prot_type = se_nacl->saved_prot_type;
		else if (tfo->tpg_check_prot_fabric_only)
			se_sess->sess_prot_type = se_nacl->saved_prot_type =
					tfo->tpg_check_prot_fabric_only(se_tpg);
		/*
		 * If the fabric module supports an ISID based TransportID,
		 * save this value in binary from the fabric I_T Nexus now.
		 */
		if (se_tpg->se_tpg_tfo->sess_get_initiator_sid != NULL) {
			memset(&buf[0], 0, PR_REG_ISID_LEN);
			se_tpg->se_tpg_tfo->sess_get_initiator_sid(se_sess,
					&buf[0], PR_REG_ISID_LEN);
			se_sess->sess_bin_isid = get_unaligned_be64(&buf[0]);
		}

		spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
		/*
		 * The se_nacl->nacl_sess pointer will be set to the
		 * last active I_T Nexus for each struct se_node_acl.
		 */
		se_nacl->nacl_sess = se_sess;

		list_add_tail(&se_sess->sess_acl_list,
			      &se_nacl->acl_sess_list);
		spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);
	}
	list_add_tail(&se_sess->sess_list, &se_tpg->tpg_sess_list);

	pr_debug("TARGET_CORE[%s]: Registered fabric_sess_ptr: %p\n",
		se_tpg->se_tpg_tfo->fabric_name, se_sess->fabric_sess_ptr);
}