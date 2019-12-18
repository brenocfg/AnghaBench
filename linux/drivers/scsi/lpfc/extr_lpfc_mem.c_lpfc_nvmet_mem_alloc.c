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
struct lpfc_hba {int /*<<< orphan*/  lpfc_nvmet_drb_pool; TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_NVMET_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  SGL_ALIGN_SZ ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
lpfc_nvmet_mem_alloc(struct lpfc_hba *phba)
{
	phba->lpfc_nvmet_drb_pool =
		dma_pool_create("lpfc_nvmet_drb_pool",
				&phba->pcidev->dev, LPFC_NVMET_DATA_BUF_SIZE,
				SGL_ALIGN_SZ, 0);
	if (!phba->lpfc_nvmet_drb_pool) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"6024 Can't enable NVME Target - no memory\n");
		return -ENOMEM;
	}
	return 0;
}