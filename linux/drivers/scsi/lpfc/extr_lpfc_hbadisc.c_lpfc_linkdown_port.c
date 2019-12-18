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
struct lpfc_vport {scalar_t__ cfg_enable_fc4_type; int /*<<< orphan*/  delayed_disc_tmo; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  fc_ns_retry; int /*<<< orphan*/  port_state; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCH_EVT_LINKDOWN ; 
 int /*<<< orphan*/  FC_DISC_DELAYED ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 scalar_t__ LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_event (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_port_link_failure (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_linkdown_port(struct lpfc_vport *vport)
{
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);

	if (vport->cfg_enable_fc4_type != LPFC_ENABLE_NVME)
		fc_host_post_event(shost, fc_get_event_number(),
				   FCH_EVT_LINKDOWN, 0);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Link Down:       state:x%x rtry:x%x flg:x%x",
		vport->port_state, vport->fc_ns_retry, vport->fc_flag);

	lpfc_port_link_failure(vport);

	/* Stop delayed Nport discovery */
	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~FC_DISC_DELAYED;
	spin_unlock_irq(shost->host_lock);
	del_timer_sync(&vport->delayed_disc_tmo);
}