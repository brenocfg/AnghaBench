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
struct enic {unsigned int intr_count; TYPE_2__* msix_entry; TYPE_1__* pdev; int /*<<< orphan*/  vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_synchronize_irqs(struct enic *enic)
{
	unsigned int i;

	switch (vnic_dev_get_intr_mode(enic->vdev)) {
	case VNIC_DEV_INTR_MODE_INTX:
	case VNIC_DEV_INTR_MODE_MSI:
		synchronize_irq(enic->pdev->irq);
		break;
	case VNIC_DEV_INTR_MODE_MSIX:
		for (i = 0; i < enic->intr_count; i++)
			synchronize_irq(enic->msix_entry[i].vector);
		break;
	default:
		break;
	}
}