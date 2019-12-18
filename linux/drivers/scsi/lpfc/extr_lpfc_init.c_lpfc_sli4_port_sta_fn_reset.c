#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {scalar_t__ intr_mode; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_INTR_ERROR ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int) ; 
 int lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_disable_intr (struct lpfc_hba*) ; 
 scalar_t__ lpfc_sli4_enable_intr (struct lpfc_hba*,scalar_t__) ; 
 int lpfc_sli4_pdev_status_reg_wait (struct lpfc_hba*) ; 
 int lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_flush_io_rings (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_sli4_port_sta_fn_reset(struct lpfc_hba *phba, int mbx_action,
			    bool en_rn_msg)
{
	int rc;
	uint32_t intr_mode;

	if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) >=
	    LPFC_SLI_INTF_IF_TYPE_2) {
		/*
		 * On error status condition, driver need to wait for port
		 * ready before performing reset.
		 */
		rc = lpfc_sli4_pdev_status_reg_wait(phba);
		if (rc)
			return rc;
	}

	/* need reset: attempt for port recovery */
	if (en_rn_msg)
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2887 Reset Needed: Attempting Port "
				"Recovery...\n");
	lpfc_offline_prep(phba, mbx_action);
	lpfc_sli_flush_io_rings(phba);
	lpfc_offline(phba);
	/* release interrupt for possible resource change */
	lpfc_sli4_disable_intr(phba);
	rc = lpfc_sli_brdrestart(phba);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"6309 Failed to restart board\n");
		return rc;
	}
	/* request and enable interrupt */
	intr_mode = lpfc_sli4_enable_intr(phba, phba->intr_mode);
	if (intr_mode == LPFC_INTR_ERROR) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3175 Failed to enable interrupt\n");
		return -EIO;
	}
	phba->intr_mode = intr_mode;
	rc = lpfc_online(phba);
	if (rc == 0)
		lpfc_unblock_mgmt_io(phba);

	return rc;
}