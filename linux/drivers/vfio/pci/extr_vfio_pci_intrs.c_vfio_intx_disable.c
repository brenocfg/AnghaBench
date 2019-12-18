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
struct vfio_pci_device {TYPE_1__* ctx; scalar_t__ num_ctx; int /*<<< orphan*/  irq_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  unmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_PCI_NUM_IRQS ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  vfio_intx_set_signal (struct vfio_pci_device*,int) ; 
 int /*<<< orphan*/  vfio_virqfd_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_intx_disable(struct vfio_pci_device *vdev)
{
	vfio_virqfd_disable(&vdev->ctx[0].unmask);
	vfio_virqfd_disable(&vdev->ctx[0].mask);
	vfio_intx_set_signal(vdev, -1);
	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	vdev->num_ctx = 0;
	kfree(vdev->ctx);
}