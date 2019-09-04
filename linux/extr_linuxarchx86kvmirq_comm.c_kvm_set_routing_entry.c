#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sint; int /*<<< orphan*/  vcpu; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_8__ {int pin; int /*<<< orphan*/  irqchip; } ;
struct kvm_kernel_irq_routing_entry {TYPE_5__ hv_sint; int /*<<< orphan*/  set; TYPE_3__ msi; TYPE_1__ irqchip; } ;
struct TYPE_13__ {int /*<<< orphan*/  sint; int /*<<< orphan*/  vcpu; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_9__ {int pin; int /*<<< orphan*/  irqchip; } ;
struct TYPE_14__ {TYPE_6__ hv_sint; TYPE_4__ msi; TYPE_2__ irqchip; } ;
struct kvm_irq_routing_entry {int type; TYPE_7__ u; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_IOAPIC_NUM_PINS ; 
#define  KVM_IRQCHIP_IOAPIC 133 
#define  KVM_IRQCHIP_PIC_MASTER 132 
#define  KVM_IRQCHIP_PIC_SLAVE 131 
#define  KVM_IRQ_ROUTING_HV_SINT 130 
#define  KVM_IRQ_ROUTING_IRQCHIP 129 
#define  KVM_IRQ_ROUTING_MSI 128 
 int PIC_NUM_PINS ; 
 int /*<<< orphan*/  irqchip_split (struct kvm*) ; 
 int /*<<< orphan*/  kvm_hv_set_sint ; 
 int /*<<< orphan*/  kvm_msi_route_invalid (struct kvm*,struct kvm_kernel_irq_routing_entry*) ; 
 int /*<<< orphan*/  kvm_set_ioapic_irq ; 
 int /*<<< orphan*/  kvm_set_msi ; 
 int /*<<< orphan*/  kvm_set_pic_irq ; 

int kvm_set_routing_entry(struct kvm *kvm,
			  struct kvm_kernel_irq_routing_entry *e,
			  const struct kvm_irq_routing_entry *ue)
{
	/* We can't check irqchip_in_kernel() here as some callers are
	 * currently inititalizing the irqchip. Other callers should therefore
	 * check kvm_arch_can_set_irq_routing() before calling this function.
	 */
	switch (ue->type) {
	case KVM_IRQ_ROUTING_IRQCHIP:
		if (irqchip_split(kvm))
			return -EINVAL;
		e->irqchip.pin = ue->u.irqchip.pin;
		switch (ue->u.irqchip.irqchip) {
		case KVM_IRQCHIP_PIC_SLAVE:
			e->irqchip.pin += PIC_NUM_PINS / 2;
			/* fall through */
		case KVM_IRQCHIP_PIC_MASTER:
			if (ue->u.irqchip.pin >= PIC_NUM_PINS / 2)
				return -EINVAL;
			e->set = kvm_set_pic_irq;
			break;
		case KVM_IRQCHIP_IOAPIC:
			if (ue->u.irqchip.pin >= KVM_IOAPIC_NUM_PINS)
				return -EINVAL;
			e->set = kvm_set_ioapic_irq;
			break;
		default:
			return -EINVAL;
		}
		e->irqchip.irqchip = ue->u.irqchip.irqchip;
		break;
	case KVM_IRQ_ROUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.address_lo = ue->u.msi.address_lo;
		e->msi.address_hi = ue->u.msi.address_hi;
		e->msi.data = ue->u.msi.data;

		if (kvm_msi_route_invalid(kvm, e))
			return -EINVAL;
		break;
	case KVM_IRQ_ROUTING_HV_SINT:
		e->set = kvm_hv_set_sint;
		e->hv_sint.vcpu = ue->u.hv_sint.vcpu;
		e->hv_sint.sint = ue->u.hv_sint.sint;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}