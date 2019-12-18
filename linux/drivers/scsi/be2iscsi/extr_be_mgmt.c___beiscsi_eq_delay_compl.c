#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ptag_state; } ;
struct beiscsi_hba {TYPE_3__* pcidev; TYPE_2__ ctrl; } ;
struct be_dma_mem {scalar_t__ size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct be_dma_mem tag_mem_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __beiscsi_mcc_compl_status (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __beiscsi_eq_delay_compl(struct beiscsi_hba *phba, unsigned int tag)
{
	struct be_dma_mem *tag_mem;

	/* status is ignored */
	__beiscsi_mcc_compl_status(phba, tag, NULL, NULL);
	tag_mem = &phba->ctrl.ptag_state[tag].tag_mem_state;
	if (tag_mem->size) {
		dma_free_coherent(&phba->pcidev->dev, tag_mem->size,
				    tag_mem->va, tag_mem->dma);
		tag_mem->size = 0;
	}
}