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
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  pdev; TYPE_1__ config; TYPE_2__* vxge_entries; TYPE_2__* entries; } ;
struct TYPE_4__ {scalar_t__ in_use; int /*<<< orphan*/  arg; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxge_rem_msix_isr(struct vxgedev *vdev)
{
	int intr_cnt;

	for (intr_cnt = 0; intr_cnt < (vdev->no_of_vpath * 2 + 1);
		intr_cnt++) {
		if (vdev->vxge_entries[intr_cnt].in_use) {
			synchronize_irq(vdev->entries[intr_cnt].vector);
			free_irq(vdev->entries[intr_cnt].vector,
				vdev->vxge_entries[intr_cnt].arg);
			vdev->vxge_entries[intr_cnt].in_use = 0;
		}
	}

	kfree(vdev->entries);
	kfree(vdev->vxge_entries);
	vdev->entries = NULL;
	vdev->vxge_entries = NULL;

	if (vdev->config.intr_type == MSI_X)
		pci_disable_msix(vdev->pdev);
}