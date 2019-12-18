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
struct TYPE_3__ {scalar_t__ oas_supported; } ;
struct TYPE_4__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {int cfg_fof; int /*<<< orphan*/ * device_data_mem_pool; TYPE_2__ sli4_hba; int /*<<< orphan*/  cfg_EnableXLane; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_sli4_oas_verify(struct lpfc_hba *phba)
{

	if (!phba->cfg_EnableXLane)
		return;

	if (phba->sli4_hba.pc_sli4_params.oas_supported) {
		phba->cfg_fof = 1;
	} else {
		phba->cfg_fof = 0;
		if (phba->device_data_mem_pool)
			mempool_destroy(phba->device_data_mem_pool);
		phba->device_data_mem_pool = NULL;
	}

	return;
}