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
struct TYPE_3__ {int max_xri; } ;
struct TYPE_4__ {TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {size_t cfg_rrq_xri_bitmap_sz; int /*<<< orphan*/  active_rrq_pool; TYPE_2__ sli4_hba; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LPFC_MEM_POOL_SIZE ; 
 int /*<<< orphan*/  mempool_create_kmalloc_pool (int /*<<< orphan*/ ,size_t) ; 

int
lpfc_mem_alloc_active_rrq_pool_s4(struct lpfc_hba *phba) {
	size_t bytes;
	int max_xri = phba->sli4_hba.max_cfg_param.max_xri;

	if (max_xri <= 0)
		return -ENOMEM;
	bytes = ((BITS_PER_LONG - 1 + max_xri) / BITS_PER_LONG) *
		  sizeof(unsigned long);
	phba->cfg_rrq_xri_bitmap_sz = bytes;
	phba->active_rrq_pool = mempool_create_kmalloc_pool(LPFC_MEM_POOL_SIZE,
							    bytes);
	if (!phba->active_rrq_pool)
		return -ENOMEM;
	else
		return 0;
}