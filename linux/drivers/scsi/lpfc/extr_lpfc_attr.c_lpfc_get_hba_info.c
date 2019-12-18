#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct lpfc_mbx_read_config {int dummy; } ;
struct TYPE_23__ {scalar_t__ rpi_used; scalar_t__ xri_used; scalar_t__ vpi_used; } ;
struct TYPE_24__ {TYPE_6__ max_cfg_param; } ;
struct TYPE_18__ {int sli_flag; } ;
struct lpfc_hba {scalar_t__ link_state; int fc_ratov; scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; TYPE_7__ sli4_hba; TYPE_2__* pport; TYPE_1__ sli; } ;
struct TYPE_25__ {scalar_t__ max_vpi; scalar_t__ avail_vpi; scalar_t__ avail_xri; scalar_t__ max_xri; scalar_t__ avail_rpi; scalar_t__ max_rpi; } ;
struct TYPE_26__ {TYPE_8__ varRdConfig; } ;
struct TYPE_20__ {struct lpfc_mbx_read_config rd_config; } ;
struct TYPE_21__ {TYPE_3__ un; } ;
struct TYPE_16__ {TYPE_9__ un; int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_22__ {TYPE_4__ mqe; TYPE_10__ mb; } ;
struct TYPE_19__ {int fc_flag; } ;
struct TYPE_17__ {TYPE_5__ u; int /*<<< orphan*/ * ctx_buf; } ;
typedef  TYPE_10__ MAILBOX_t ;
typedef  TYPE_11__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_OFFLINE_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LPFC_BLOCK_MGMT_IO ; 
 scalar_t__ LPFC_HBA_READY ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 scalar_t__ LPFC_MAX_VPI ; 
 int LPFC_SLI_ACTIVE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_READ_CONFIG ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 int /*<<< orphan*/  OWN_HOST ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_mbx_read_config*) ; 
 int /*<<< orphan*/  lpfc_mbx_rd_conf_rpi_count ; 
 int /*<<< orphan*/  lpfc_mbx_rd_conf_vpi_count ; 
 int /*<<< orphan*/  lpfc_mbx_rd_conf_xri_count ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_11__*,int) ; 
 TYPE_11__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_get_hba_info(struct lpfc_hba *phba,
		  uint32_t *mxri, uint32_t *axri,
		  uint32_t *mrpi, uint32_t *arpi,
		  uint32_t *mvpi, uint32_t *avpi)
{
	struct lpfc_mbx_read_config *rd_config;
	LPFC_MBOXQ_t *pmboxq;
	MAILBOX_t *pmb;
	int rc = 0;
	uint32_t max_vpi;

	/*
	 * prevent udev from issuing mailbox commands until the port is
	 * configured.
	 */
	if (phba->link_state < LPFC_LINK_DOWN ||
	    !phba->mbox_mem_pool ||
	    (phba->sli.sli_flag & LPFC_SLI_ACTIVE) == 0)
		return 0;

	if (phba->sli.sli_flag & LPFC_BLOCK_MGMT_IO)
		return 0;

	pmboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmboxq)
		return 0;
	memset(pmboxq, 0, sizeof (LPFC_MBOXQ_t));

	pmb = &pmboxq->u.mb;
	pmb->mbxCommand = MBX_READ_CONFIG;
	pmb->mbxOwner = OWN_HOST;
	pmboxq->ctx_buf = NULL;

	if (phba->pport->fc_flag & FC_OFFLINE_MODE)
		rc = MBX_NOT_FINISHED;
	else
		rc = lpfc_sli_issue_mbox_wait(phba, pmboxq, phba->fc_ratov * 2);

	if (rc != MBX_SUCCESS) {
		if (rc != MBX_TIMEOUT)
			mempool_free(pmboxq, phba->mbox_mem_pool);
		return 0;
	}

	if (phba->sli_rev == LPFC_SLI_REV4) {
		rd_config = &pmboxq->u.mqe.un.rd_config;
		if (mrpi)
			*mrpi = bf_get(lpfc_mbx_rd_conf_rpi_count, rd_config);
		if (arpi)
			*arpi = bf_get(lpfc_mbx_rd_conf_rpi_count, rd_config) -
					phba->sli4_hba.max_cfg_param.rpi_used;
		if (mxri)
			*mxri = bf_get(lpfc_mbx_rd_conf_xri_count, rd_config);
		if (axri)
			*axri = bf_get(lpfc_mbx_rd_conf_xri_count, rd_config) -
					phba->sli4_hba.max_cfg_param.xri_used;

		/* Account for differences with SLI-3.  Get vpi count from
		 * mailbox data and subtract one for max vpi value.
		 */
		max_vpi = (bf_get(lpfc_mbx_rd_conf_vpi_count, rd_config) > 0) ?
			(bf_get(lpfc_mbx_rd_conf_vpi_count, rd_config) - 1) : 0;

		/* Limit the max we support */
		if (max_vpi > LPFC_MAX_VPI)
			max_vpi = LPFC_MAX_VPI;
		if (mvpi)
			*mvpi = max_vpi;
		if (avpi)
			*avpi = max_vpi - phba->sli4_hba.max_cfg_param.vpi_used;
	} else {
		if (mrpi)
			*mrpi = pmb->un.varRdConfig.max_rpi;
		if (arpi)
			*arpi = pmb->un.varRdConfig.avail_rpi;
		if (mxri)
			*mxri = pmb->un.varRdConfig.max_xri;
		if (axri)
			*axri = pmb->un.varRdConfig.avail_xri;
		if (mvpi)
			*mvpi = pmb->un.varRdConfig.max_vpi;
		if (avpi) {
			/* avail_vpi is only valid if link is up and ready */
			if (phba->link_state == LPFC_HBA_READY)
				*avpi = pmb->un.varRdConfig.avail_vpi;
			else
				*avpi = pmb->un.varRdConfig.max_vpi;
		}
	}

	mempool_free(pmboxq, phba->mbox_mem_pool);
	return 1;
}