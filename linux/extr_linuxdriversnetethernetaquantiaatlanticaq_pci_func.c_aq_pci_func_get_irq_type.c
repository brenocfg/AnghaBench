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
struct aq_nic_s {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ msi_enabled; scalar_t__ msix_enabled; } ;

/* Variables and functions */
 unsigned int AQ_HW_IRQ_LEGACY ; 
 unsigned int AQ_HW_IRQ_MSIX ; 

unsigned int aq_pci_func_get_irq_type(struct aq_nic_s *self)
{
	if (self->pdev->msix_enabled)
		return AQ_HW_IRQ_MSIX;
	if (self->pdev->msi_enabled)
		return AQ_HW_IRQ_MSIX;
	return AQ_HW_IRQ_LEGACY;
}