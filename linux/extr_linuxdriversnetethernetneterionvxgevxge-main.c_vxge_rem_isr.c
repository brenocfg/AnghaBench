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
struct TYPE_3__ {scalar_t__ intr_type; } ;
struct vxgedev {TYPE_2__* pdev; TYPE_1__ config; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ INTA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vxgedev*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_rem_msix_isr (struct vxgedev*) ; 

__attribute__((used)) static void vxge_rem_isr(struct vxgedev *vdev)
{
	if (IS_ENABLED(CONFIG_PCI_MSI) &&
	    vdev->config.intr_type == MSI_X) {
		vxge_rem_msix_isr(vdev);
	} else if (vdev->config.intr_type == INTA) {
			synchronize_irq(vdev->pdev->irq);
			free_irq(vdev->pdev->irq, vdev);
	}
}