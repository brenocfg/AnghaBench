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
struct lpfc_vport {int load_flag; scalar_t__ cfg_enable_fc4_type; int fc_flag; scalar_t__ fc_ns_retry; struct lpfc_hba* phba; } ;
struct lpfc_hba {int sli3_options; struct lpfc_vport* pport; int /*<<< orphan*/  link_flag; int /*<<< orphan*/  fc_linkspeed; int /*<<< orphan*/  fc_topology; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCH_EVT_LINKUP ; 
 int FC_ABORT_DISCOVERY ; 
 int FC_LBIT ; 
 int FC_NDISC_ACTIVE ; 
 int FC_NLP_MORE ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int FC_RSCN_DISCOVERY ; 
 int FC_RSCN_MODE ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 scalar_t__ LPFC_ENABLE_NVME ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_event (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_linkup_cleanup_nodes (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_linkup_port(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;

	if ((vport->load_flag & FC_UNLOADING) != 0)
		return;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Link Up:         top:x%x speed:x%x flg:x%x",
		phba->fc_topology, phba->fc_linkspeed, phba->link_flag);

	/* If NPIV is not enabled, only bring the physical port up */
	if (!(phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) &&
		(vport != phba->pport))
		return;

	if (vport->cfg_enable_fc4_type != LPFC_ENABLE_NVME)
		fc_host_post_event(shost, fc_get_event_number(),
				   FCH_EVT_LINKUP, 0);

	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~(FC_PT2PT | FC_PT2PT_PLOGI | FC_ABORT_DISCOVERY |
			    FC_RSCN_MODE | FC_NLP_MORE | FC_RSCN_DISCOVERY);
	vport->fc_flag |= FC_NDISC_ACTIVE;
	vport->fc_ns_retry = 0;
	spin_unlock_irq(shost->host_lock);

	if (vport->fc_flag & FC_LBIT)
		lpfc_linkup_cleanup_nodes(vport);

}