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
struct lpfc_sli {int /*<<< orphan*/  mbox_tmo; } ;
struct lpfc_hba {int cfg_enable_fc4_type; int /*<<< orphan*/  eq_delay_work; int /*<<< orphan*/  hb_tmofunc; int /*<<< orphan*/  eratt_poll; int /*<<< orphan*/  fabric_block_timer; int /*<<< orphan*/  luns; int /*<<< orphan*/  devicelock; int /*<<< orphan*/  fcf_conn_rec_list; int /*<<< orphan*/  elsbuf; int /*<<< orphan*/  fabric_iocb_list; int /*<<< orphan*/  lpfc_scsi_buf_list_put; int /*<<< orphan*/  scsi_buf_list_put_lock; int /*<<< orphan*/  lpfc_scsi_buf_list_get; int /*<<< orphan*/  scsi_buf_list_get_lock; scalar_t__ nvmet_support; int /*<<< orphan*/  work_waitq; int /*<<< orphan*/  wait_4_mlo_m_q; int /*<<< orphan*/  work_list; int /*<<< orphan*/  port_list; int /*<<< orphan*/  port_list_lock; int /*<<< orphan*/  ndlp_lock; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  fast_event_count; struct lpfc_sli sli; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_ENABLE_FCP ; 
 int LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_fabric_block_timeout ; 
 int /*<<< orphan*/  lpfc_hb_eq_delay_work ; 
 int /*<<< orphan*/  lpfc_hb_timeout ; 
 int /*<<< orphan*/  lpfc_mbox_timeout ; 
 int /*<<< orphan*/  lpfc_poll_eratt ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_setup_driver_resource_phase1(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;

	/*
	 * Driver resources common to all SLI revisions
	 */
	atomic_set(&phba->fast_event_count, 0);
	spin_lock_init(&phba->hbalock);

	/* Initialize ndlp management spinlock */
	spin_lock_init(&phba->ndlp_lock);

	/* Initialize port_list spinlock */
	spin_lock_init(&phba->port_list_lock);
	INIT_LIST_HEAD(&phba->port_list);

	INIT_LIST_HEAD(&phba->work_list);
	init_waitqueue_head(&phba->wait_4_mlo_m_q);

	/* Initialize the wait queue head for the kernel thread */
	init_waitqueue_head(&phba->work_waitq);

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"1403 Protocols supported %s %s %s\n",
			((phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP) ?
				"SCSI" : " "),
			((phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) ?
				"NVME" : " "),
			(phba->nvmet_support ? "NVMET" : " "));

	/* Initialize the IO buffer list used by driver for SLI3 SCSI */
	spin_lock_init(&phba->scsi_buf_list_get_lock);
	INIT_LIST_HEAD(&phba->lpfc_scsi_buf_list_get);
	spin_lock_init(&phba->scsi_buf_list_put_lock);
	INIT_LIST_HEAD(&phba->lpfc_scsi_buf_list_put);

	/* Initialize the fabric iocb list */
	INIT_LIST_HEAD(&phba->fabric_iocb_list);

	/* Initialize list to save ELS buffers */
	INIT_LIST_HEAD(&phba->elsbuf);

	/* Initialize FCF connection rec list */
	INIT_LIST_HEAD(&phba->fcf_conn_rec_list);

	/* Initialize OAS configuration list */
	spin_lock_init(&phba->devicelock);
	INIT_LIST_HEAD(&phba->luns);

	/* MBOX heartbeat timer */
	timer_setup(&psli->mbox_tmo, lpfc_mbox_timeout, 0);
	/* Fabric block timer */
	timer_setup(&phba->fabric_block_timer, lpfc_fabric_block_timeout, 0);
	/* EA polling mode timer */
	timer_setup(&phba->eratt_poll, lpfc_poll_eratt, 0);
	/* Heartbeat timer */
	timer_setup(&phba->hb_tmofunc, lpfc_hb_timeout, 0);

	INIT_DELAYED_WORK(&phba->eq_delay_work, lpfc_hb_eq_delay_work);

	return 0;
}