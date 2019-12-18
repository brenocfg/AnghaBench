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
struct se_session {struct fc_port* fabric_sess_ptr; } ;
struct scsi_qla_host {TYPE_2__* hw; } ;
struct fc_port {struct scsi_qla_host* vha; } ;
struct TYPE_3__ {int /*<<< orphan*/  sess_lock; } ;
struct TYPE_4__ {TYPE_1__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_sess_cmd_list_set_waiting (struct se_session*) ; 
 int /*<<< orphan*/  tcm_qla2xxx_put_sess (struct fc_port*) ; 

__attribute__((used)) static void tcm_qla2xxx_close_session(struct se_session *se_sess)
{
	struct fc_port *sess = se_sess->fabric_sess_ptr;
	struct scsi_qla_host *vha;
	unsigned long flags;

	BUG_ON(!sess);
	vha = sess->vha;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	target_sess_cmd_list_set_waiting(se_sess);
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	tcm_qla2xxx_put_sess(sess);
}