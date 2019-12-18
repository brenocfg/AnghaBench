#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int bbRcvSizeMsb; } ;
struct TYPE_11__ {TYPE_2__ cmn; } ;
struct lpfc_vport {int fc_flag; scalar_t__ port_state; TYPE_3__ fc_sparam; } ;
struct TYPE_9__ {int /*<<< orphan*/  bbscn_params; } ;
struct lpfc_hba {scalar_t__ sli_rev; int hba_flag; int link_flag; scalar_t__ fc_topology; int /*<<< orphan*/  mbox_mem_pool; TYPE_1__ sli4_hba; scalar_t__ cfg_enable_bbcr; scalar_t__ bbcredit_support; } ;
struct TYPE_12__ {scalar_t__ mbxStatus; } ;
struct TYPE_13__ {TYPE_4__ mb; } ;
struct TYPE_14__ {TYPE_5__ u; struct lpfc_vport* vport; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_LBIT ; 
 int FC_PT2PT ; 
 int FC_PUBLIC_LOOP ; 
 int HBA_FCOE_MODE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 scalar_t__ LPFC_FLOGI ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int LS_LOOPBACK_MODE ; 
 int bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_bbscn_def ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_initial_flogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_clear_la (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_6__*,int /*<<< orphan*/ ) ; 

void
lpfc_mbx_cmpl_local_config_link(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport *vport = pmb->vport;
	uint8_t bbscn = 0;

	if (pmb->u.mb.mbxStatus)
		goto out;

	mempool_free(pmb, phba->mbox_mem_pool);

	/* don't perform discovery for SLI4 loopback diagnostic test */
	if ((phba->sli_rev == LPFC_SLI_REV4) &&
	    !(phba->hba_flag & HBA_FCOE_MODE) &&
	    (phba->link_flag & LS_LOOPBACK_MODE))
		return;

	if (phba->fc_topology == LPFC_TOPOLOGY_LOOP &&
	    vport->fc_flag & FC_PUBLIC_LOOP &&
	    !(vport->fc_flag & FC_LBIT)) {
			/* Need to wait for FAN - use discovery timer
			 * for timeout.  port_state is identically
			 * LPFC_LOCAL_CFG_LINK while waiting for FAN
			 */
			lpfc_set_disctmo(vport);
			return;
	}

	/* Start discovery by sending a FLOGI. port_state is identically
	 * LPFC_FLOGI while waiting for FLOGI cmpl
	 */
	if (vport->port_state != LPFC_FLOGI) {
		if (phba->bbcredit_support && phba->cfg_enable_bbcr) {
			bbscn = bf_get(lpfc_bbscn_def,
				       &phba->sli4_hba.bbscn_params);
			vport->fc_sparam.cmn.bbRcvSizeMsb &= 0xf;
			vport->fc_sparam.cmn.bbRcvSizeMsb |= (bbscn << 4);
		}
		lpfc_initial_flogi(vport);
	} else if (vport->fc_flag & FC_PT2PT) {
		lpfc_disc_start(vport);
	}
	return;

out:
	lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
			 "0306 CONFIG_LINK mbxStatus error x%x "
			 "HBA state x%x\n",
			 pmb->u.mb.mbxStatus, vport->port_state);
	mempool_free(pmb, phba->mbox_mem_pool);

	lpfc_linkdown(phba);

	lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
			 "0200 CONFIG_LINK bad hba state x%x\n",
			 vport->port_state);

	lpfc_issue_clear_la(phba, vport);
	return;
}