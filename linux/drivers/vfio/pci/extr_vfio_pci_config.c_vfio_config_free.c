#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfio_pci_device {int /*<<< orphan*/ * msi_perm; int /*<<< orphan*/ * pci_config_map; int /*<<< orphan*/ * vconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void vfio_config_free(struct vfio_pci_device *vdev)
{
	kfree(vdev->vconfig);
	vdev->vconfig = NULL;
	kfree(vdev->pci_config_map);
	vdev->pci_config_map = NULL;
	kfree(vdev->msi_perm);
	vdev->msi_perm = NULL;
}