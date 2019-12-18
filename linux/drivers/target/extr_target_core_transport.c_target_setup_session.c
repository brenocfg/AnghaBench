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
struct se_session {int /*<<< orphan*/  se_node_acl; } ;
struct se_portal_group {int dummy; } ;
typedef  enum target_prot_op { ____Placeholder_target_prot_op } target_prot_op ;

/* Variables and functions */
 int EACCES ; 
 struct se_session* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct se_session*) ; 
 int /*<<< orphan*/  core_tpg_check_initiator_node_acl (struct se_portal_group*,unsigned char*) ; 
 struct se_session* transport_alloc_session (int) ; 
 int /*<<< orphan*/  transport_free_session (struct se_session*) ; 
 struct se_session* transport_init_session_tags (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  transport_register_session (struct se_portal_group*,int /*<<< orphan*/ ,struct se_session*,void*) ; 

struct se_session *
target_setup_session(struct se_portal_group *tpg,
		     unsigned int tag_num, unsigned int tag_size,
		     enum target_prot_op prot_op,
		     const char *initiatorname, void *private,
		     int (*callback)(struct se_portal_group *,
				     struct se_session *, void *))
{
	struct se_session *sess;

	/*
	 * If the fabric driver is using percpu-ida based pre allocation
	 * of I/O descriptor tags, go ahead and perform that setup now..
	 */
	if (tag_num != 0)
		sess = transport_init_session_tags(tag_num, tag_size, prot_op);
	else
		sess = transport_alloc_session(prot_op);

	if (IS_ERR(sess))
		return sess;

	sess->se_node_acl = core_tpg_check_initiator_node_acl(tpg,
					(unsigned char *)initiatorname);
	if (!sess->se_node_acl) {
		transport_free_session(sess);
		return ERR_PTR(-EACCES);
	}
	/*
	 * Go ahead and perform any remaining fabric setup that is
	 * required before transport_register_session().
	 */
	if (callback != NULL) {
		int rc = callback(tpg, sess, private);
		if (rc) {
			transport_free_session(sess);
			return ERR_PTR(rc);
		}
	}

	transport_register_session(tpg, sess->se_node_acl, sess, private);
	return sess;
}