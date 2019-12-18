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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct virtio_pci_device {scalar_t__ ioaddr; TYPE_1__ vdev; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct virtio_pci_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  unregister_virtio_device (TYPE_1__*) ; 
 int /*<<< orphan*/  virtio_pci_legacy_remove (struct virtio_pci_device*) ; 
 int /*<<< orphan*/  virtio_pci_modern_remove (struct virtio_pci_device*) ; 

__attribute__((used)) static void virtio_pci_remove(struct pci_dev *pci_dev)
{
	struct virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	struct device *dev = get_device(&vp_dev->vdev.dev);

	pci_disable_sriov(pci_dev);

	unregister_virtio_device(&vp_dev->vdev);

	if (vp_dev->ioaddr)
		virtio_pci_legacy_remove(vp_dev);
	else
		virtio_pci_modern_remove(vp_dev);

	pci_disable_device(pci_dev);
	put_device(dev);
}