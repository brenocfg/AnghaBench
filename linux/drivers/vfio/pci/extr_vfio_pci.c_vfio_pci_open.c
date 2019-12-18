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
struct vfio_pci_device {TYPE_1__* reflck; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int vfio_pci_enable (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_spapr_pci_eeh_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_pci_open(void *device_data)
{
	struct vfio_pci_device *vdev = device_data;
	int ret = 0;

	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	mutex_lock(&vdev->reflck->lock);

	if (!vdev->refcnt) {
		ret = vfio_pci_enable(vdev);
		if (ret)
			goto error;

		vfio_spapr_pci_eeh_open(vdev->pdev);
	}
	vdev->refcnt++;
error:
	mutex_unlock(&vdev->reflck->lock);
	if (ret)
		module_put(THIS_MODULE);
	return ret;
}