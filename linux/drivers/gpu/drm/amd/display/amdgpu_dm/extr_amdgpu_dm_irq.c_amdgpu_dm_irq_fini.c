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
struct irq_list_head {int /*<<< orphan*/  work; } ;
struct TYPE_2__ {struct irq_list_head* irq_handler_list_low_tab; } ;
struct amdgpu_device {TYPE_1__ dm; } ;

/* Variables and functions */
 int DAL_IRQ_SOURCES_NUMBER ; 
 int /*<<< orphan*/  DM_IRQ_TABLE_LOCK (struct amdgpu_device*,unsigned long) ; 
 int /*<<< orphan*/  DM_IRQ_TABLE_UNLOCK (struct amdgpu_device*,unsigned long) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 

void amdgpu_dm_irq_fini(struct amdgpu_device *adev)
{
	int src;
	struct irq_list_head *lh;
	unsigned long irq_table_flags;
	DRM_DEBUG_KMS("DM_IRQ: releasing resources.\n");
	for (src = 0; src < DAL_IRQ_SOURCES_NUMBER; src++) {
		DM_IRQ_TABLE_LOCK(adev, irq_table_flags);
		/* The handler was removed from the table,
		 * it means it is safe to flush all the 'work'
		 * (because no code can schedule a new one). */
		lh = &adev->dm.irq_handler_list_low_tab[src];
		DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);
		flush_work(&lh->work);
	}
}