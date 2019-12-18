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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  fc_adisc_cnt; int /*<<< orphan*/  fc_plogi_cnt; int /*<<< orphan*/  port_state; int /*<<< orphan*/  work_port_lock; int /*<<< orphan*/  work_port_events; int /*<<< orphan*/  fc_disctmo; int /*<<< orphan*/  fc_ns_retry; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;

/* Variables and functions */
 int FC_DISC_TMO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  WORKER_DISC_TMO ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
lpfc_can_disctmo(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	unsigned long iflags;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"can disc timer:  state:x%x rtry:x%x flg:x%x",
		vport->port_state, vport->fc_ns_retry, vport->fc_flag);

	/* Turn off discovery timer if its running */
	if (vport->fc_flag & FC_DISC_TMO) {
		spin_lock_irqsave(shost->host_lock, iflags);
		vport->fc_flag &= ~FC_DISC_TMO;
		spin_unlock_irqrestore(shost->host_lock, iflags);
		del_timer_sync(&vport->fc_disctmo);
		spin_lock_irqsave(&vport->work_port_lock, iflags);
		vport->work_port_events &= ~WORKER_DISC_TMO;
		spin_unlock_irqrestore(&vport->work_port_lock, iflags);
	}

	/* Cancel Discovery Timer state <hba_state> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0248 Cancel Discovery Timer state x%x "
			 "Data: x%x x%x x%x\n",
			 vport->port_state, vport->fc_flag,
			 vport->fc_plogi_cnt, vport->fc_adisc_cnt);
	return 0;
}