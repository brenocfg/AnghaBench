#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int u16 ;
struct phys_addr {int dummy; } ;
struct hwi_controller {TYPE_4__* wrb_context; struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {TYPE_1__** pasync_ctx; } ;
struct hd_async_context {scalar_t__* cid_to_async_cri_map; } ;
struct TYPE_7__ {size_t cxns_per_ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/  ulp_supported; } ;
struct be_ctrl_info {int dummy; } ;
struct beiscsi_hba {int optic_state; TYPE_3__ params; TYPE_2__ fw_config; struct hwi_controller* phwi_ctrlr; struct be_ctrl_info ctrl; } ;
struct TYPE_8__ {size_t cid; } ;
struct TYPE_5__ {int num_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_DEFQ_DATA ; 
 int /*<<< orphan*/  BEISCSI_DEFQ_HDR ; 
 int BEISCSI_GET_ULP_FROM_CRI (struct hwi_controller*,size_t) ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int BEISCSI_ULP_COUNT ; 
 struct hd_async_context* HWI_GET_ASYNC_PDU_CTX (struct hwi_controller*,int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int be_mcc_queues_create (struct beiscsi_hba*,struct hwi_context_memory*) ; 
 int beiscsi_check_supported_fw (struct be_ctrl_info*,struct beiscsi_hba*) ; 
 int beiscsi_create_cqs (struct beiscsi_hba*,struct hwi_context_memory*) ; 
 int beiscsi_create_def_data (struct beiscsi_hba*,struct hwi_context_memory*,struct hwi_controller*,unsigned int,int) ; 
 int beiscsi_create_def_hdr (struct beiscsi_hba*,struct hwi_context_memory*,struct hwi_controller*,unsigned int,int) ; 
 int beiscsi_create_eqs (struct beiscsi_hba*,struct hwi_context_memory*) ; 
 int beiscsi_create_wrb_rings (struct beiscsi_hba*,struct hwi_context_memory*,struct hwi_controller*) ; 
 int /*<<< orphan*/  beiscsi_hdq_post_handles (struct beiscsi_hba*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int beiscsi_post_pages (struct beiscsi_hba*) ; 
 int beiscsi_post_template_hdr (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_cleanup_port (struct beiscsi_hba*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwi_init_port(struct beiscsi_hba *phba)
{
	struct hwi_controller *phwi_ctrlr;
	struct hwi_context_memory *phwi_context;
	unsigned int def_pdu_ring_sz;
	struct be_ctrl_info *ctrl = &phba->ctrl;
	int status, ulp_num;
	u16 nbufs;

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;
	/* set port optic state to unknown */
	phba->optic_state = 0xff;

	status = beiscsi_create_eqs(phba, phwi_context);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : EQ not created\n");
		goto error;
	}

	status = be_mcc_queues_create(phba, phwi_context);
	if (status != 0)
		goto error;

	status = beiscsi_check_supported_fw(ctrl, phba);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Unsupported fw version\n");
		goto error;
	}

	status = beiscsi_create_cqs(phba, phwi_context);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : CQ not created\n");
		goto error;
	}

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, &phba->fw_config.ulp_supported)) {
			nbufs = phwi_context->pasync_ctx[ulp_num]->num_entries;
			def_pdu_ring_sz = nbufs * sizeof(struct phys_addr);

			status = beiscsi_create_def_hdr(phba, phwi_context,
							phwi_ctrlr,
							def_pdu_ring_sz,
							ulp_num);
			if (status != 0) {
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
					    "BM_%d : Default Header not created for ULP : %d\n",
					    ulp_num);
				goto error;
			}

			status = beiscsi_create_def_data(phba, phwi_context,
							 phwi_ctrlr,
							 def_pdu_ring_sz,
							 ulp_num);
			if (status != 0) {
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
					    "BM_%d : Default Data not created for ULP : %d\n",
					    ulp_num);
				goto error;
			}
			/**
			 * Now that the default PDU rings have been created,
			 * let EP know about it.
			 */
			beiscsi_hdq_post_handles(phba, BEISCSI_DEFQ_HDR,
						 ulp_num, nbufs);
			beiscsi_hdq_post_handles(phba, BEISCSI_DEFQ_DATA,
						 ulp_num, nbufs);
		}
	}

	status = beiscsi_post_pages(phba);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Post SGL Pages Failed\n");
		goto error;
	}

	status = beiscsi_post_template_hdr(phba);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Template HDR Posting for CXN Failed\n");
	}

	status = beiscsi_create_wrb_rings(phba,	phwi_context, phwi_ctrlr);
	if (status != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : WRB Rings not created\n");
		goto error;
	}

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		uint16_t async_arr_idx = 0;

		if (test_bit(ulp_num, &phba->fw_config.ulp_supported)) {
			uint16_t cri = 0;
			struct hd_async_context *pasync_ctx;

			pasync_ctx = HWI_GET_ASYNC_PDU_CTX(
				     phwi_ctrlr, ulp_num);
			for (cri = 0; cri <
			     phba->params.cxns_per_ctrl; cri++) {
				if (ulp_num == BEISCSI_GET_ULP_FROM_CRI
					       (phwi_ctrlr, cri))
					pasync_ctx->cid_to_async_cri_map[
					phwi_ctrlr->wrb_context[cri].cid] =
					async_arr_idx++;
			}
		}
	}

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BM_%d : hwi_init_port success\n");
	return 0;

error:
	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
		    "BM_%d : hwi_init_port failed");
	hwi_cleanup_port(phba);
	return status;
}