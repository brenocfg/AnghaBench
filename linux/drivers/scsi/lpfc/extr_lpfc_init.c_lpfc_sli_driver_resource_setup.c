#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ulp_bde64 {int dummy; } ;
struct sli4_sge {int dummy; } ;
struct lpfc_sli_ring {int dummy; } ;
struct TYPE_6__ {scalar_t__ sli3_ring; } ;
struct lpfc_hba {int work_ha_mask; int cfg_sg_seg_cnt; scalar_t__ sli_rev; int cfg_sg_dma_buf_size; int cfg_total_seg_cnt; int /*<<< orphan*/ * lpfc_sg_dma_buf_pool; int /*<<< orphan*/  cfg_sriov_nr_virtfn; void* lpfc_cmd_rsp_buf_pool; TYPE_2__* pcidev; scalar_t__ max_vports; int /*<<< orphan*/  max_vpi; scalar_t__ cfg_enable_bg; TYPE_1__ sli; int /*<<< orphan*/  menlo_flag; int /*<<< orphan*/  fcp_poll_timer; } ;
struct fcp_rsp {int dummy; } ;
struct fcp_cmnd {int dummy; } ;
struct TYPE_10__ {int sg_tablesize; } ;
struct TYPE_9__ {int sg_tablesize; } ;
struct TYPE_8__ {int sg_tablesize; } ;
struct TYPE_7__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPL_ALIGN_SZ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HA_ERATT ; 
 int HA_LATT ; 
 int HA_MBATT ; 
 int HA_RXMASK ; 
 int /*<<< orphan*/  HBA_MENLO_SUPPORT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_FCP ; 
 int LOG_INIT ; 
 int LPFC_DEFAULT_MENLO_SG_SEG_CNT ; 
 int LPFC_ELS_RING ; 
 int LPFC_MAX_SG_SEG_CNT ; 
 int LPFC_MAX_SG_SEG_CNT_DIF ; 
 int /*<<< orphan*/  LPFC_MAX_VPI ; 
 int /*<<< orphan*/  LPFC_SLI3_MAX_RING ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ PCI_DEVICE_ID_HORNET ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_get_cfgparam (struct lpfc_hba*) ; 
 scalar_t__ lpfc_mem_alloc (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mem_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_poll_timeout ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,...) ; 
 int lpfc_setup_driver_resource_phase1 (struct lpfc_hba*) ; 
 int lpfc_sli_probe_sriov_nr_virtfn (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_queue_init (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_setup (struct lpfc_hba*) ; 
 TYPE_5__ lpfc_template ; 
 TYPE_4__ lpfc_template_no_hr ; 
 TYPE_3__ lpfc_vport_template ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli_driver_resource_setup(struct lpfc_hba *phba)
{
	int rc, entry_sz;

	/*
	 * Initialize timers used by driver
	 */

	/* FCP polling mode timer */
	timer_setup(&phba->fcp_poll_timer, lpfc_poll_timeout, 0);

	/* Host attention work mask setup */
	phba->work_ha_mask = (HA_ERATT | HA_MBATT | HA_LATT);
	phba->work_ha_mask |= (HA_RXMASK << (LPFC_ELS_RING * 4));

	/* Get all the module params for configuring this host */
	lpfc_get_cfgparam(phba);
	/* Set up phase-1 common device driver resources */

	rc = lpfc_setup_driver_resource_phase1(phba);
	if (rc)
		return -ENODEV;

	if (phba->pcidev->device == PCI_DEVICE_ID_HORNET) {
		phba->menlo_flag |= HBA_MENLO_SUPPORT;
		/* check for menlo minimum sg count */
		if (phba->cfg_sg_seg_cnt < LPFC_DEFAULT_MENLO_SG_SEG_CNT)
			phba->cfg_sg_seg_cnt = LPFC_DEFAULT_MENLO_SG_SEG_CNT;
	}

	if (!phba->sli.sli3_ring)
		phba->sli.sli3_ring = kcalloc(LPFC_SLI3_MAX_RING,
					      sizeof(struct lpfc_sli_ring),
					      GFP_KERNEL);
	if (!phba->sli.sli3_ring)
		return -ENOMEM;

	/*
	 * Since lpfc_sg_seg_cnt is module parameter, the sg_dma_buf_size
	 * used to create the sg_dma_buf_pool must be dynamically calculated.
	 */

	/* Initialize the host templates the configured values. */
	lpfc_vport_template.sg_tablesize = phba->cfg_sg_seg_cnt;
	lpfc_template_no_hr.sg_tablesize = phba->cfg_sg_seg_cnt;
	lpfc_template.sg_tablesize = phba->cfg_sg_seg_cnt;

	if (phba->sli_rev == LPFC_SLI_REV4)
		entry_sz = sizeof(struct sli4_sge);
	else
		entry_sz = sizeof(struct ulp_bde64);

	/* There are going to be 2 reserved BDEs: 1 FCP cmnd + 1 FCP rsp */
	if (phba->cfg_enable_bg) {
		/*
		 * The scsi_buf for a T10-DIF I/O will hold the FCP cmnd,
		 * the FCP rsp, and a BDE for each. Sice we have no control
		 * over how many protection data segments the SCSI Layer
		 * will hand us (ie: there could be one for every block
		 * in the IO), we just allocate enough BDEs to accomidate
		 * our max amount and we need to limit lpfc_sg_seg_cnt to
		 * minimize the risk of running out.
		 */
		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			(LPFC_MAX_SG_SEG_CNT * entry_sz);

		if (phba->cfg_sg_seg_cnt > LPFC_MAX_SG_SEG_CNT_DIF)
			phba->cfg_sg_seg_cnt = LPFC_MAX_SG_SEG_CNT_DIF;

		/* Total BDEs in BPL for scsi_sg_list and scsi_sg_prot_list */
		phba->cfg_total_seg_cnt = LPFC_MAX_SG_SEG_CNT;
	} else {
		/*
		 * The scsi_buf for a regular I/O will hold the FCP cmnd,
		 * the FCP rsp, a BDE for each, and a BDE for up to
		 * cfg_sg_seg_cnt data segments.
		 */
		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			((phba->cfg_sg_seg_cnt + 2) * entry_sz);

		/* Total BDEs in BPL for scsi_sg_list */
		phba->cfg_total_seg_cnt = phba->cfg_sg_seg_cnt + 2;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT | LOG_FCP,
			"9088 sg_tablesize:%d dmabuf_size:%d total_bde:%d\n",
			phba->cfg_sg_seg_cnt, phba->cfg_sg_dma_buf_size,
			phba->cfg_total_seg_cnt);

	phba->max_vpi = LPFC_MAX_VPI;
	/* This will be set to correct value after config_port mbox */
	phba->max_vports = 0;

	/*
	 * Initialize the SLI Layer to run with lpfc HBAs.
	 */
	lpfc_sli_setup(phba);
	lpfc_sli_queue_init(phba);

	/* Allocate device driver memory */
	if (lpfc_mem_alloc(phba, BPL_ALIGN_SZ))
		return -ENOMEM;

	phba->lpfc_sg_dma_buf_pool =
		dma_pool_create("lpfc_sg_dma_buf_pool",
				&phba->pcidev->dev, phba->cfg_sg_dma_buf_size,
				BPL_ALIGN_SZ, 0);

	if (!phba->lpfc_sg_dma_buf_pool)
		goto fail_free_mem;

	phba->lpfc_cmd_rsp_buf_pool =
			dma_pool_create("lpfc_cmd_rsp_buf_pool",
					&phba->pcidev->dev,
					sizeof(struct fcp_cmnd) +
					sizeof(struct fcp_rsp),
					BPL_ALIGN_SZ, 0);

	if (!phba->lpfc_cmd_rsp_buf_pool)
		goto fail_free_dma_buf_pool;

	/*
	 * Enable sr-iov virtual functions if supported and configured
	 * through the module parameter.
	 */
	if (phba->cfg_sriov_nr_virtfn > 0) {
		rc = lpfc_sli_probe_sriov_nr_virtfn(phba,
						 phba->cfg_sriov_nr_virtfn);
		if (rc) {
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"2808 Requested number of SR-IOV "
					"virtual functions (%d) is not "
					"supported\n",
					phba->cfg_sriov_nr_virtfn);
			phba->cfg_sriov_nr_virtfn = 0;
		}
	}

	return 0;

fail_free_dma_buf_pool:
	dma_pool_destroy(phba->lpfc_sg_dma_buf_pool);
	phba->lpfc_sg_dma_buf_pool = NULL;
fail_free_mem:
	lpfc_mem_free(phba);
	return -ENOMEM;
}