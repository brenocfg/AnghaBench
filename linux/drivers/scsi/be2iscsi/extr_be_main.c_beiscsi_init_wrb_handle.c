#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wrb_handle {unsigned int wrb_index; struct wrb_handle* pwrb; } ;
struct iscsi_wrb {unsigned int wrb_index; struct iscsi_wrb* pwrb; } ;
struct hwi_wrb_context {struct wrb_handle** pwrb_handle_basestd; struct wrb_handle** pwrb_handle_base; int /*<<< orphan*/  wrb_lock; scalar_t__ wrb_handles_available; scalar_t__ free_index; scalar_t__ alloc_index; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {void* be_wrbq; } ;
struct TYPE_4__ {unsigned int cxns_per_ctrl; unsigned int wrbs_per_cxn; } ;
struct beiscsi_hba {TYPE_2__ params; struct hwi_controller* phwi_ctrlr; struct be_mem_descriptor* init_mem; } ;
struct be_queue_info {int dummy; } ;
struct be_mem_descriptor {TYPE_1__* mem_array; } ;
struct TYPE_3__ {int size; struct wrb_handle* virtual_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWI_MEM_WRB ; 
 int /*<<< orphan*/  HWI_MEM_WRBH ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wrb_handle**) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int beiscsi_init_wrb_handle(struct beiscsi_hba *phba)
{
	struct be_mem_descriptor *mem_descr_wrbh, *mem_descr_wrb;
	struct hwi_context_memory *phwi_ctxt;
	struct wrb_handle *pwrb_handle = NULL;
	struct hwi_controller *phwi_ctrlr;
	struct hwi_wrb_context *pwrb_context;
	struct iscsi_wrb *pwrb = NULL;
	unsigned int num_cxn_wrbh = 0;
	unsigned int num_cxn_wrb = 0, j, idx = 0, index;

	mem_descr_wrbh = phba->init_mem;
	mem_descr_wrbh += HWI_MEM_WRBH;

	mem_descr_wrb = phba->init_mem;
	mem_descr_wrb += HWI_MEM_WRB;
	phwi_ctrlr = phba->phwi_ctrlr;

	/* Allocate memory for WRBQ */
	phwi_ctxt = phwi_ctrlr->phwi_ctxt;
	phwi_ctxt->be_wrbq = kcalloc(phba->params.cxns_per_ctrl,
				     sizeof(struct be_queue_info),
				     GFP_KERNEL);
	if (!phwi_ctxt->be_wrbq) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : WRBQ Mem Alloc Failed\n");
		return -ENOMEM;
	}

	for (index = 0; index < phba->params.cxns_per_ctrl; index++) {
		pwrb_context = &phwi_ctrlr->wrb_context[index];
		pwrb_context->pwrb_handle_base =
				kcalloc(phba->params.wrbs_per_cxn,
					sizeof(struct wrb_handle *),
					GFP_KERNEL);
		if (!pwrb_context->pwrb_handle_base) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : Mem Alloc Failed. Failing to load\n");
			goto init_wrb_hndl_failed;
		}
		pwrb_context->pwrb_handle_basestd =
				kcalloc(phba->params.wrbs_per_cxn,
					sizeof(struct wrb_handle *),
					GFP_KERNEL);
		if (!pwrb_context->pwrb_handle_basestd) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : Mem Alloc Failed. Failing to load\n");
			goto init_wrb_hndl_failed;
		}
		if (!num_cxn_wrbh) {
			pwrb_handle =
				mem_descr_wrbh->mem_array[idx].virtual_address;
			num_cxn_wrbh = ((mem_descr_wrbh->mem_array[idx].size) /
					((sizeof(struct wrb_handle)) *
					 phba->params.wrbs_per_cxn));
			idx++;
		}
		pwrb_context->alloc_index = 0;
		pwrb_context->wrb_handles_available = 0;
		pwrb_context->free_index = 0;

		if (num_cxn_wrbh) {
			for (j = 0; j < phba->params.wrbs_per_cxn; j++) {
				pwrb_context->pwrb_handle_base[j] = pwrb_handle;
				pwrb_context->pwrb_handle_basestd[j] =
								pwrb_handle;
				pwrb_context->wrb_handles_available++;
				pwrb_handle->wrb_index = j;
				pwrb_handle++;
			}
			num_cxn_wrbh--;
		}
		spin_lock_init(&pwrb_context->wrb_lock);
	}
	idx = 0;
	for (index = 0; index < phba->params.cxns_per_ctrl; index++) {
		pwrb_context = &phwi_ctrlr->wrb_context[index];
		if (!num_cxn_wrb) {
			pwrb = mem_descr_wrb->mem_array[idx].virtual_address;
			num_cxn_wrb = (mem_descr_wrb->mem_array[idx].size) /
				((sizeof(struct iscsi_wrb) *
				  phba->params.wrbs_per_cxn));
			idx++;
		}

		if (num_cxn_wrb) {
			for (j = 0; j < phba->params.wrbs_per_cxn; j++) {
				pwrb_handle = pwrb_context->pwrb_handle_base[j];
				pwrb_handle->pwrb = pwrb;
				pwrb++;
			}
			num_cxn_wrb--;
		}
	}
	return 0;
init_wrb_hndl_failed:
	for (j = index; j > 0; j--) {
		pwrb_context = &phwi_ctrlr->wrb_context[j];
		kfree(pwrb_context->pwrb_handle_base);
		kfree(pwrb_context->pwrb_handle_basestd);
	}
	return -ENOMEM;
}