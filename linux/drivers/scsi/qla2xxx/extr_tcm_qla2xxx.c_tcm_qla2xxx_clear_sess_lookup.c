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
struct tcm_qla2xxx_nacl {int dummy; } ;
struct tcm_qla2xxx_lport {int dummy; } ;
struct se_session {int dummy; } ;
struct fc_port {int /*<<< orphan*/  loop_id; int /*<<< orphan*/  d_id; struct se_session* se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_id_to_be_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_qla2xxx_set_sess_by_loop_id (struct tcm_qla2xxx_lport*,int /*<<< orphan*/ *,struct tcm_qla2xxx_nacl*,struct se_session*,struct fc_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_qla2xxx_set_sess_by_s_id (struct tcm_qla2xxx_lport*,int /*<<< orphan*/ *,struct tcm_qla2xxx_nacl*,struct se_session*,struct fc_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcm_qla2xxx_clear_sess_lookup(struct tcm_qla2xxx_lport *lport,
		struct tcm_qla2xxx_nacl *nacl, struct fc_port *sess)
{
	struct se_session *se_sess = sess->se_sess;

	tcm_qla2xxx_set_sess_by_s_id(lport, NULL, nacl, se_sess,
				     sess, port_id_to_be_id(sess->d_id));
	tcm_qla2xxx_set_sess_by_loop_id(lport, NULL, nacl, se_sess,
				sess, sess->loop_id);
}