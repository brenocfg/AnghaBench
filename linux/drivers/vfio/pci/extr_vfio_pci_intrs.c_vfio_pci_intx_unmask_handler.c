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
struct vfio_pci_device {int /*<<< orphan*/  irqlock; TYPE_1__* ctx; scalar_t__ pci_2_3; int /*<<< orphan*/  virq_disabled; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int masked; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_intx (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  pci_check_and_unmask_intx (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vfio_pci_intx_unmask_handler(void *opaque, void *unused)
{
	struct vfio_pci_device *vdev = opaque;
	struct pci_dev *pdev = vdev->pdev;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&vdev->irqlock, flags);

	/*
	 * Unmasking comes from ioctl or config, so again, have the
	 * physical bit follow the virtual even when not using INTx.
	 */
	if (unlikely(!is_intx(vdev))) {
		if (vdev->pci_2_3)
			pci_intx(pdev, 1);
	} else if (vdev->ctx[0].masked && !vdev->virq_disabled) {
		/*
		 * A pending interrupt here would immediately trigger,
		 * but we can avoid that overhead by just re-sending
		 * the interrupt to the user.
		 */
		if (vdev->pci_2_3) {
			if (!pci_check_and_unmask_intx(pdev))
				ret = 1;
		} else
			enable_irq(pdev->irq);

		vdev->ctx[0].masked = (ret > 0);
	}

	spin_unlock_irqrestore(&vdev->irqlock, flags);

	return ret;
}