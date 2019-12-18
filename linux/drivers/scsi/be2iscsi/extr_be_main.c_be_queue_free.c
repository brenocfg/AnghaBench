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
struct beiscsi_hba {TYPE_1__* pcidev; } ;
struct be_dma_mem {int /*<<< orphan*/ * va; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct be_queue_info {struct be_dma_mem dma_mem; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_queue_free(struct beiscsi_hba *phba, struct be_queue_info *q)
{
	struct be_dma_mem *mem = &q->dma_mem;
	if (mem->va) {
		dma_free_coherent(&phba->pcidev->dev, mem->size,
			mem->va, mem->dma);
		mem->va = NULL;
	}
}