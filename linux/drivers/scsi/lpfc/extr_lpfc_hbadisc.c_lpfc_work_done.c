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
typedef  int uint32_t ;
struct lpfc_vport {int work_port_events; int /*<<< orphan*/  work_port_lock; } ;
struct lpfc_sli_ring {int flag; } ;
struct TYPE_2__ {int fcf_flag; } ;
struct lpfc_hba {int work_ha; scalar_t__ pci_dev_grp; int hba_flag; int max_vports; scalar_t__ link_state; int link_flag; scalar_t__ sli_rev; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HCregaddr; int /*<<< orphan*/  data_flags; struct lpfc_vport* pport; TYPE_1__ fcf; } ;

/* Variables and functions */
 int ASYNC_EVENT ; 
 int ELS_XRI_ABORT_EVENT ; 
 int FCF_REDISC_EVT ; 
 int HA_ERATT ; 
 int HA_LATT ; 
 int HA_MBATT ; 
 int HA_RXMASK ; 
 int HBA_POST_RECEIVE_BUFFER ; 
 int HBA_RRQ_ACTIVE ; 
 int HBA_SP_QUEUE_EVT ; 
 int HC_R0INT_ENA ; 
 int /*<<< orphan*/  LPFC_DATA_READY ; 
 int LPFC_DEFERRED_RING_EVENT ; 
 int /*<<< orphan*/  LPFC_ELS_HBQ ; 
 int LPFC_ELS_RING ; 
 scalar_t__ LPFC_LINK_UP ; 
 scalar_t__ LPFC_PCI_DEV_OC ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int LPFC_STOP_IOCB_EVENT ; 
 int LS_MDS_LOOPBACK ; 
 int WORKER_DELAYED_DISC_TMO ; 
 int WORKER_DISC_TMO ; 
 int WORKER_ELS_TMO ; 
 int WORKER_FABRIC_BLOCK_TMO ; 
 int WORKER_HB_TMO ; 
 int WORKER_MBOX_TMO ; 
 int WORKER_RAMP_DOWN_QUEUE ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debugfs_slow_ring_trc (struct lpfc_hba*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_delayed_disc_timeout_handler (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_disc_timeout_handler (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_drain_txq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_els_timeout_handler (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_handle_eratt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_handle_latt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_handle_rrq_active (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hb_timeout_handler (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mbox_timeout_handler (struct lpfc_hba*) ; 
 struct lpfc_sli_ring* lpfc_phba_elsring (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_ramp_down_queue_handler (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_async_event_proc (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_els_xri_abort_event_proc (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_fcf_redisc_event_proc (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_post_async_mbox (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_handle_mb_event (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_handle_slow_ring_event (struct lpfc_hba*,struct lpfc_sli_ring*,int) ; 
 int /*<<< orphan*/  lpfc_sli_hbqbuf_add_hbqs (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unblock_fabric_iocbs (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_work_list_done (struct lpfc_hba*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_work_done(struct lpfc_hba *phba)
{
	struct lpfc_sli_ring *pring;
	uint32_t ha_copy, status, control, work_port_events;
	struct lpfc_vport **vports;
	struct lpfc_vport *vport;
	int i;

	spin_lock_irq(&phba->hbalock);
	ha_copy = phba->work_ha;
	phba->work_ha = 0;
	spin_unlock_irq(&phba->hbalock);

	/* First, try to post the next mailbox command to SLI4 device */
	if (phba->pci_dev_grp == LPFC_PCI_DEV_OC)
		lpfc_sli4_post_async_mbox(phba);

	if (ha_copy & HA_ERATT)
		/* Handle the error attention event */
		lpfc_handle_eratt(phba);

	if (ha_copy & HA_MBATT)
		lpfc_sli_handle_mb_event(phba);

	if (ha_copy & HA_LATT)
		lpfc_handle_latt(phba);

	/* Process SLI4 events */
	if (phba->pci_dev_grp == LPFC_PCI_DEV_OC) {
		if (phba->hba_flag & HBA_RRQ_ACTIVE)
			lpfc_handle_rrq_active(phba);
		if (phba->hba_flag & ELS_XRI_ABORT_EVENT)
			lpfc_sli4_els_xri_abort_event_proc(phba);
		if (phba->hba_flag & ASYNC_EVENT)
			lpfc_sli4_async_event_proc(phba);
		if (phba->hba_flag & HBA_POST_RECEIVE_BUFFER) {
			spin_lock_irq(&phba->hbalock);
			phba->hba_flag &= ~HBA_POST_RECEIVE_BUFFER;
			spin_unlock_irq(&phba->hbalock);
			lpfc_sli_hbqbuf_add_hbqs(phba, LPFC_ELS_HBQ);
		}
		if (phba->fcf.fcf_flag & FCF_REDISC_EVT)
			lpfc_sli4_fcf_redisc_event_proc(phba);
	}

	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL)
		for (i = 0; i <= phba->max_vports; i++) {
			/*
			 * We could have no vports in array if unloading, so if
			 * this happens then just use the pport
			 */
			if (vports[i] == NULL && i == 0)
				vport = phba->pport;
			else
				vport = vports[i];
			if (vport == NULL)
				break;
			spin_lock_irq(&vport->work_port_lock);
			work_port_events = vport->work_port_events;
			vport->work_port_events &= ~work_port_events;
			spin_unlock_irq(&vport->work_port_lock);
			if (work_port_events & WORKER_DISC_TMO)
				lpfc_disc_timeout_handler(vport);
			if (work_port_events & WORKER_ELS_TMO)
				lpfc_els_timeout_handler(vport);
			if (work_port_events & WORKER_HB_TMO)
				lpfc_hb_timeout_handler(phba);
			if (work_port_events & WORKER_MBOX_TMO)
				lpfc_mbox_timeout_handler(phba);
			if (work_port_events & WORKER_FABRIC_BLOCK_TMO)
				lpfc_unblock_fabric_iocbs(phba);
			if (work_port_events & WORKER_RAMP_DOWN_QUEUE)
				lpfc_ramp_down_queue_handler(phba);
			if (work_port_events & WORKER_DELAYED_DISC_TMO)
				lpfc_delayed_disc_timeout_handler(vport);
		}
	lpfc_destroy_vport_work_array(phba, vports);

	pring = lpfc_phba_elsring(phba);
	status = (ha_copy & (HA_RXMASK  << (4*LPFC_ELS_RING)));
	status >>= (4*LPFC_ELS_RING);
	if (pring && (status & HA_RXMASK ||
		      pring->flag & LPFC_DEFERRED_RING_EVENT ||
		      phba->hba_flag & HBA_SP_QUEUE_EVT)) {
		if (pring->flag & LPFC_STOP_IOCB_EVENT) {
			pring->flag |= LPFC_DEFERRED_RING_EVENT;
			/* Preserve legacy behavior. */
			if (!(phba->hba_flag & HBA_SP_QUEUE_EVT))
				set_bit(LPFC_DATA_READY, &phba->data_flags);
		} else {
			if (phba->link_state >= LPFC_LINK_UP ||
			    phba->link_flag & LS_MDS_LOOPBACK) {
				pring->flag &= ~LPFC_DEFERRED_RING_EVENT;
				lpfc_sli_handle_slow_ring_event(phba, pring,
								(status &
								HA_RXMASK));
			}
		}
		if (phba->sli_rev == LPFC_SLI_REV4)
			lpfc_drain_txq(phba);
		/*
		 * Turn on Ring interrupts
		 */
		if (phba->sli_rev <= LPFC_SLI_REV3) {
			spin_lock_irq(&phba->hbalock);
			control = readl(phba->HCregaddr);
			if (!(control & (HC_R0INT_ENA << LPFC_ELS_RING))) {
				lpfc_debugfs_slow_ring_trc(phba,
					"WRK Enable ring: cntl:x%x hacopy:x%x",
					control, ha_copy, 0);

				control |= (HC_R0INT_ENA << LPFC_ELS_RING);
				writel(control, phba->HCregaddr);
				readl(phba->HCregaddr); /* flush */
			} else {
				lpfc_debugfs_slow_ring_trc(phba,
					"WRK Ring ok:     cntl:x%x hacopy:x%x",
					control, ha_copy, 0);
			}
			spin_unlock_irq(&phba->hbalock);
		}
	}
	lpfc_work_list_done(phba);
}