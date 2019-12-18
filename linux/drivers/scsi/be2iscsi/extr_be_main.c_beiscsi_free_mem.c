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
struct beiscsi_hba {struct be_mem_descriptor* phwi_ctrlr; struct be_mem_descriptor* init_mem; TYPE_1__* pcidev; } ;
struct TYPE_6__ {scalar_t__ address; } ;
struct TYPE_7__ {TYPE_2__ a64; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct be_mem_descriptor {int num_elements; struct be_mem_descriptor* wrb_context; struct be_mem_descriptor* mem_array; TYPE_4__ bus_address; int /*<<< orphan*/  virtual_address; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SE_MEM_MAX ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct be_mem_descriptor*) ; 

__attribute__((used)) static void beiscsi_free_mem(struct beiscsi_hba *phba)
{
	struct be_mem_descriptor *mem_descr;
	int i, j;

	mem_descr = phba->init_mem;
	i = 0;
	j = 0;
	for (i = 0; i < SE_MEM_MAX; i++) {
		for (j = mem_descr->num_elements; j > 0; j--) {
			dma_free_coherent(&phba->pcidev->dev,
			  mem_descr->mem_array[j - 1].size,
			  mem_descr->mem_array[j - 1].virtual_address,
			  (unsigned long)mem_descr->mem_array[j - 1].
			  bus_address.u.a64.address);
		}

		kfree(mem_descr->mem_array);
		mem_descr++;
	}
	kfree(phba->init_mem);
	kfree(phba->phwi_ctrlr->wrb_context);
	kfree(phba->phwi_ctrlr);
}