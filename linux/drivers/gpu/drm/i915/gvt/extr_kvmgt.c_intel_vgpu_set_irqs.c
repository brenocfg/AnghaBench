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
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  VFIO_IRQ_SET_ACTION_MASK 132 
#define  VFIO_IRQ_SET_ACTION_TRIGGER 131 
 int VFIO_IRQ_SET_ACTION_TYPE_MASK ; 
#define  VFIO_IRQ_SET_ACTION_UNMASK 130 
#define  VFIO_PCI_INTX_IRQ_INDEX 129 
#define  VFIO_PCI_MSI_IRQ_INDEX 128 
 int intel_vgpu_set_intx_mask (struct intel_vgpu*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int intel_vgpu_set_intx_trigger (struct intel_vgpu*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int intel_vgpu_set_intx_unmask (struct intel_vgpu*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int intel_vgpu_set_msi_trigger (struct intel_vgpu*,unsigned int,unsigned int,unsigned int,int,void*) ; 

__attribute__((used)) static int intel_vgpu_set_irqs(struct intel_vgpu *vgpu, u32 flags,
		unsigned int index, unsigned int start, unsigned int count,
		void *data)
{
	int (*func)(struct intel_vgpu *vgpu, unsigned int index,
			unsigned int start, unsigned int count, u32 flags,
			void *data) = NULL;

	switch (index) {
	case VFIO_PCI_INTX_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_MASK:
			func = intel_vgpu_set_intx_mask;
			break;
		case VFIO_IRQ_SET_ACTION_UNMASK:
			func = intel_vgpu_set_intx_unmask;
			break;
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			func = intel_vgpu_set_intx_trigger;
			break;
		}
		break;
	case VFIO_PCI_MSI_IRQ_INDEX:
		switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IRQ_SET_ACTION_MASK:
		case VFIO_IRQ_SET_ACTION_UNMASK:
			/* XXX Need masking support exported */
			break;
		case VFIO_IRQ_SET_ACTION_TRIGGER:
			func = intel_vgpu_set_msi_trigger;
			break;
		}
		break;
	}

	if (!func)
		return -ENOTTY;

	return func(vgpu, index, start, count, flags, data);
}