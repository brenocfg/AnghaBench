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
struct lpfc_hba {int /*<<< orphan*/  lpfc_sg_dma_buf_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
lpfc_nvmet_buf_free(struct lpfc_hba *phba, void *virt, dma_addr_t dma)
{
	dma_pool_free(phba->lpfc_sg_dma_buf_pool, virt, dma);
}