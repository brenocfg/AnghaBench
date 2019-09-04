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
struct irq_list_head {int /*<<< orphan*/  work; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/ * irq_handler_list_high_tab; struct irq_list_head* irq_handler_list_low_tab; int /*<<< orphan*/  irq_handler_list_table_lock; } ;
struct amdgpu_device {TYPE_1__ dm; } ;

/* Variables and functions */
 int DAL_IRQ_SOURCES_NUMBER ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_irq_work_func ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int amdgpu_dm_irq_init(struct amdgpu_device *adev)
{
	int src;
	struct irq_list_head *lh;

	DRM_DEBUG_KMS("DM_IRQ\n");

	spin_lock_init(&adev->dm.irq_handler_list_table_lock);

	for (src = 0; src < DAL_IRQ_SOURCES_NUMBER; src++) {
		/* low context handler list init */
		lh = &adev->dm.irq_handler_list_low_tab[src];
		INIT_LIST_HEAD(&lh->head);
		INIT_WORK(&lh->work, dm_irq_work_func);

		/* high context handler init */
		INIT_LIST_HEAD(&adev->dm.irq_handler_list_high_tab[src]);
	}

	return 0;
}