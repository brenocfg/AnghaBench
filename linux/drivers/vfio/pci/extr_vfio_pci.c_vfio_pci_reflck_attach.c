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
struct vfio_pci_device {int /*<<< orphan*/  reflck; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_is_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_probe_reset_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reflck_lock ; 
 scalar_t__ vfio_pci_for_each_slot_or_bus (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfio_pci_reflck_alloc () ; 
 int /*<<< orphan*/  vfio_pci_reflck_find ; 

__attribute__((used)) static int vfio_pci_reflck_attach(struct vfio_pci_device *vdev)
{
	bool slot = !pci_probe_reset_slot(vdev->pdev->slot);

	mutex_lock(&reflck_lock);

	if (pci_is_root_bus(vdev->pdev->bus) ||
	    vfio_pci_for_each_slot_or_bus(vdev->pdev, vfio_pci_reflck_find,
					  &vdev->reflck, slot) <= 0)
		vdev->reflck = vfio_pci_reflck_alloc();

	mutex_unlock(&reflck_lock);

	return PTR_ERR_OR_ZERO(vdev->reflck);
}