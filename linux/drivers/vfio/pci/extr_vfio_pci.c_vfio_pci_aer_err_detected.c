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
struct vfio_pci_device {int /*<<< orphan*/  igate; scalar_t__ err_trigger; } ;
struct vfio_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vfio_pci_device* vfio_device_data (struct vfio_device*) ; 
 struct vfio_device* vfio_device_get_from_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 

__attribute__((used)) static pci_ers_result_t vfio_pci_aer_err_detected(struct pci_dev *pdev,
						  pci_channel_state_t state)
{
	struct vfio_pci_device *vdev;
	struct vfio_device *device;

	device = vfio_device_get_from_dev(&pdev->dev);
	if (device == NULL)
		return PCI_ERS_RESULT_DISCONNECT;

	vdev = vfio_device_data(device);
	if (vdev == NULL) {
		vfio_device_put(device);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	mutex_lock(&vdev->igate);

	if (vdev->err_trigger)
		eventfd_signal(vdev->err_trigger, 1);

	mutex_unlock(&vdev->igate);

	vfio_device_put(device);

	return PCI_ERS_RESULT_CAN_RECOVER;
}