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
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct vbox_private {TYPE_2__ ddev; int /*<<< orphan*/  hotplug_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_irq_install (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_hotplug_worker ; 
 int /*<<< orphan*/  vbox_update_mode_hints (struct vbox_private*) ; 

int vbox_irq_init(struct vbox_private *vbox)
{
	INIT_WORK(&vbox->hotplug_work, vbox_hotplug_worker);
	vbox_update_mode_hints(vbox);

	return drm_irq_install(&vbox->ddev, vbox->ddev.pdev->irq);
}