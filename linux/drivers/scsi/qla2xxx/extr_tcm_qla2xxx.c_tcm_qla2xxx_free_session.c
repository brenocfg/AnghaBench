#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcm_qla2xxx_lport {int dummy; } ;
struct se_session {int dummy; } ;
struct qla_tgt {struct qla_hw_data* ha; } ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
struct fc_port {struct se_session* se_sess; struct qla_tgt* tgt; } ;
struct TYPE_4__ {struct tcm_qla2xxx_lport* target_lport_ptr; } ;
struct TYPE_5__ {TYPE_1__ vha_tgt; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 TYPE_2__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  target_remove_session (struct se_session*) ; 
 int /*<<< orphan*/  target_wait_for_sess_cmds (struct se_session*) ; 

__attribute__((used)) static void tcm_qla2xxx_free_session(struct fc_port *sess)
{
	struct qla_tgt *tgt = sess->tgt;
	struct qla_hw_data *ha = tgt->ha;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	struct se_session *se_sess;
	struct tcm_qla2xxx_lport *lport;

	BUG_ON(in_interrupt());

	se_sess = sess->se_sess;
	if (!se_sess) {
		pr_err("struct fc_port->se_sess is NULL\n");
		dump_stack();
		return;
	}

	lport = vha->vha_tgt.target_lport_ptr;
	if (!lport) {
		pr_err("Unable to locate struct tcm_qla2xxx_lport\n");
		dump_stack();
		return;
	}
	target_wait_for_sess_cmds(se_sess);

	target_remove_session(se_sess);
}