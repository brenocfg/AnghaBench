#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_pci_device {struct vfio_pci_device* pm_save; int /*<<< orphan*/  ioeventfds_lock; struct vfio_pci_device* region; int /*<<< orphan*/  reflck; } ;
struct TYPE_3__ {int /*<<< orphan*/  iommu_group; } ;
struct pci_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int VGA_RSRC_LEGACY_IO ; 
 int VGA_RSRC_LEGACY_MEM ; 
 int VGA_RSRC_NORMAL_IO ; 
 int VGA_RSRC_NORMAL_MEM ; 
 int /*<<< orphan*/  disable_idle_d3 ; 
 int /*<<< orphan*/  kfree (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct vfio_pci_device* vfio_del_group_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  vfio_iommu_group_put (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ vfio_pci_is_vga (struct pci_dev*) ; 
 int /*<<< orphan*/  vfio_pci_reflck_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_pci_set_power_state (struct vfio_pci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_client_register (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_set_legacy_decoding (struct pci_dev*,int) ; 

__attribute__((used)) static void vfio_pci_remove(struct pci_dev *pdev)
{
	struct vfio_pci_device *vdev;

	vdev = vfio_del_group_dev(&pdev->dev);
	if (!vdev)
		return;

	vfio_pci_reflck_put(vdev->reflck);

	vfio_iommu_group_put(pdev->dev.iommu_group, &pdev->dev);
	kfree(vdev->region);
	mutex_destroy(&vdev->ioeventfds_lock);

	if (!disable_idle_d3)
		vfio_pci_set_power_state(vdev, PCI_D0);

	kfree(vdev->pm_save);
	kfree(vdev);

	if (vfio_pci_is_vga(pdev)) {
		vga_client_register(pdev, NULL, NULL, NULL);
		vga_set_legacy_decoding(pdev,
				VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM |
				VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM);
	}
}