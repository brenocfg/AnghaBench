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
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int VFIO_PCI_INTX_IRQ_INDEX ; 
 int VFIO_PCI_MSI_IRQ_INDEX ; 

__attribute__((used)) static int intel_vgpu_get_irq_count(struct intel_vgpu *vgpu, int type)
{
	if (type == VFIO_PCI_INTX_IRQ_INDEX || type == VFIO_PCI_MSI_IRQ_INDEX)
		return 1;

	return 0;
}