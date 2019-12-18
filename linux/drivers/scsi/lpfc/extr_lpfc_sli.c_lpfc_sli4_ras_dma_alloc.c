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
typedef  int uint32_t ;
struct TYPE_3__ {void* virt; int /*<<< orphan*/  phys; } ;
struct lpfc_ras_fwlog {int fw_buffcount; int /*<<< orphan*/  fwlog_buff_list; TYPE_1__ lwpd; } ;
struct lpfc_hba {TYPE_2__* pcidev; struct lpfc_ras_fwlog ras_fwlog; } ;
struct lpfc_dmabuf {int buffer_tag; int /*<<< orphan*/  list; void* virt; int /*<<< orphan*/  phys; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_RAS_MAX_ENTRY_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_ras_dma_free (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_sli4_ras_dma_alloc(struct lpfc_hba *phba,
			uint32_t fwlog_buff_count)
{
	struct lpfc_ras_fwlog *ras_fwlog = &phba->ras_fwlog;
	struct lpfc_dmabuf *dmabuf;
	int rc = 0, i = 0;

	/* Initialize List */
	INIT_LIST_HEAD(&ras_fwlog->fwlog_buff_list);

	/* Allocate memory for the LWPD */
	ras_fwlog->lwpd.virt = dma_alloc_coherent(&phba->pcidev->dev,
					    sizeof(uint32_t) * 2,
					    &ras_fwlog->lwpd.phys,
					    GFP_KERNEL);
	if (!ras_fwlog->lwpd.virt) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"6185 LWPD Memory Alloc Failed\n");

		return -ENOMEM;
	}

	ras_fwlog->fw_buffcount = fwlog_buff_count;
	for (i = 0; i < ras_fwlog->fw_buffcount; i++) {
		dmabuf = kzalloc(sizeof(struct lpfc_dmabuf),
				 GFP_KERNEL);
		if (!dmabuf) {
			rc = -ENOMEM;
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"6186 Memory Alloc failed FW logging");
			goto free_mem;
		}

		dmabuf->virt = dma_alloc_coherent(&phba->pcidev->dev,
						  LPFC_RAS_MAX_ENTRY_SIZE,
						  &dmabuf->phys, GFP_KERNEL);
		if (!dmabuf->virt) {
			kfree(dmabuf);
			rc = -ENOMEM;
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"6187 DMA Alloc Failed FW logging");
			goto free_mem;
		}
		dmabuf->buffer_tag = i;
		list_add_tail(&dmabuf->list, &ras_fwlog->fwlog_buff_list);
	}

free_mem:
	if (rc)
		lpfc_sli4_ras_dma_free(phba);

	return rc;
}