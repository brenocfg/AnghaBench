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
struct work_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* irq_handler_list_low_tab; } ;
struct amdgpu_device {TYPE_2__ dm; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
struct TYPE_3__ {struct work_struct work; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IRQ_TABLE_LOCK (struct amdgpu_device*,unsigned long) ; 
 int /*<<< orphan*/  DM_IRQ_TABLE_UNLOCK (struct amdgpu_device*,unsigned long) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (struct work_struct*) ; 

__attribute__((used)) static void amdgpu_dm_irq_schedule_work(struct amdgpu_device *adev,
					enum dc_irq_source irq_source)
{
	unsigned long irq_table_flags;
	struct work_struct *work = NULL;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	if (!list_empty(&adev->dm.irq_handler_list_low_tab[irq_source].head))
		work = &adev->dm.irq_handler_list_low_tab[irq_source].work;

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

	if (work) {
		if (!schedule_work(work))
			DRM_INFO("amdgpu_dm_irq_schedule_work FAILED src %d\n",
						irq_source);
	}

}