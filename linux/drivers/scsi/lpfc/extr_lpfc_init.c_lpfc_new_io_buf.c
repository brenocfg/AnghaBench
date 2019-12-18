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
typedef  scalar_t__ uint16_t ;
struct lpfc_iocbq {struct lpfc_io_buf* context1; int /*<<< orphan*/  sli4_xritag; scalar_t__ sli4_lxritag; } ;
struct lpfc_io_buf {int /*<<< orphan*/  list; int /*<<< orphan*/  buf_lock; struct lpfc_iocbq cur_iocbq; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  dma_phys_sgl; scalar_t__ data; scalar_t__ dma_sgl; int /*<<< orphan*/  dma_cmd_rsp_list; int /*<<< orphan*/  dma_sgl_xtra_list; } ;
struct TYPE_2__ {scalar_t__ io_xri_cnt; int /*<<< orphan*/ * xri_ids; } ;
struct lpfc_hba {int sli3_options; TYPE_1__ sli4_hba; int /*<<< orphan*/  lpfc_sg_dma_buf_pool; int /*<<< orphan*/  nvmet_support; scalar_t__ cfg_xpsgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 int LPFC_SLI3_BG_ENABLED ; 
 scalar_t__ NO_XRI ; 
 int SLI4_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_io_buf*) ; 
 struct lpfc_io_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  lpfc_sli4_free_xri (struct lpfc_hba*,scalar_t__) ; 
 scalar_t__ lpfc_sli4_next_xritag (struct lpfc_hba*) ; 
 int lpfc_sli4_post_io_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lpfc_sli_next_iotag (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  nvme_nblist ; 
 int /*<<< orphan*/  post_nblist ; 
 int /*<<< orphan*/  prep_nblist ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
lpfc_new_io_buf(struct lpfc_hba *phba, int num_to_alloc)
{
	struct lpfc_io_buf *lpfc_ncmd;
	struct lpfc_iocbq *pwqeq;
	uint16_t iotag, lxri = 0;
	int bcnt, num_posted;
	LIST_HEAD(prep_nblist);
	LIST_HEAD(post_nblist);
	LIST_HEAD(nvme_nblist);

	phba->sli4_hba.io_xri_cnt = 0;
	for (bcnt = 0; bcnt < num_to_alloc; bcnt++) {
		lpfc_ncmd = kzalloc(sizeof(*lpfc_ncmd), GFP_KERNEL);
		if (!lpfc_ncmd)
			break;
		/*
		 * Get memory from the pci pool to map the virt space to
		 * pci bus space for an I/O. The DMA buffer includes the
		 * number of SGE's necessary to support the sg_tablesize.
		 */
		lpfc_ncmd->data = dma_pool_zalloc(phba->lpfc_sg_dma_buf_pool,
						  GFP_KERNEL,
						  &lpfc_ncmd->dma_handle);
		if (!lpfc_ncmd->data) {
			kfree(lpfc_ncmd);
			break;
		}

		if (phba->cfg_xpsgl && !phba->nvmet_support) {
			INIT_LIST_HEAD(&lpfc_ncmd->dma_sgl_xtra_list);
		} else {
			/*
			 * 4K Page alignment is CRITICAL to BlockGuard, double
			 * check to be sure.
			 */
			if ((phba->sli3_options & LPFC_SLI3_BG_ENABLED) &&
			    (((unsigned long)(lpfc_ncmd->data) &
			    (unsigned long)(SLI4_PAGE_SIZE - 1)) != 0)) {
				lpfc_printf_log(phba, KERN_ERR, LOG_FCP,
						"3369 Memory alignment err: "
						"addr=%lx\n",
						(unsigned long)lpfc_ncmd->data);
				dma_pool_free(phba->lpfc_sg_dma_buf_pool,
					      lpfc_ncmd->data,
					      lpfc_ncmd->dma_handle);
				kfree(lpfc_ncmd);
				break;
			}
		}

		INIT_LIST_HEAD(&lpfc_ncmd->dma_cmd_rsp_list);

		lxri = lpfc_sli4_next_xritag(phba);
		if (lxri == NO_XRI) {
			dma_pool_free(phba->lpfc_sg_dma_buf_pool,
				      lpfc_ncmd->data, lpfc_ncmd->dma_handle);
			kfree(lpfc_ncmd);
			break;
		}
		pwqeq = &lpfc_ncmd->cur_iocbq;

		/* Allocate iotag for lpfc_ncmd->cur_iocbq. */
		iotag = lpfc_sli_next_iotag(phba, pwqeq);
		if (iotag == 0) {
			dma_pool_free(phba->lpfc_sg_dma_buf_pool,
				      lpfc_ncmd->data, lpfc_ncmd->dma_handle);
			kfree(lpfc_ncmd);
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
					"6121 Failed to allocate IOTAG for"
					" XRI:0x%x\n", lxri);
			lpfc_sli4_free_xri(phba, lxri);
			break;
		}
		pwqeq->sli4_lxritag = lxri;
		pwqeq->sli4_xritag = phba->sli4_hba.xri_ids[lxri];
		pwqeq->context1 = lpfc_ncmd;

		/* Initialize local short-hand pointers. */
		lpfc_ncmd->dma_sgl = lpfc_ncmd->data;
		lpfc_ncmd->dma_phys_sgl = lpfc_ncmd->dma_handle;
		lpfc_ncmd->cur_iocbq.context1 = lpfc_ncmd;
		spin_lock_init(&lpfc_ncmd->buf_lock);

		/* add the nvme buffer to a post list */
		list_add_tail(&lpfc_ncmd->list, &post_nblist);
		phba->sli4_hba.io_xri_cnt++;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_NVME,
			"6114 Allocate %d out of %d requested new NVME "
			"buffers\n", bcnt, num_to_alloc);

	/* post the list of nvme buffer sgls to port if available */
	if (!list_empty(&post_nblist))
		num_posted = lpfc_sli4_post_io_sgl_list(
				phba, &post_nblist, bcnt);
	else
		num_posted = 0;

	return num_posted;
}