#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_eq {size_t vector; } ;
struct TYPE_5__ {int* vector_list; } ;
struct TYPE_6__ {scalar_t__ intr_mode; TYPE_2__ msix; TYPE_1__* pdev; } ;
struct ocrdma_dev {TYPE_3__ nic_info; } ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 scalar_t__ BE_INTERRUPT_MODE_INTX ; 

int ocrdma_get_irq(struct ocrdma_dev *dev, struct ocrdma_eq *eq)
{
	int irq;

	if (dev->nic_info.intr_mode == BE_INTERRUPT_MODE_INTX)
		irq = dev->nic_info.pdev->irq;
	else
		irq = dev->nic_info.msix.vector_list[eq->vector];
	return irq;
}