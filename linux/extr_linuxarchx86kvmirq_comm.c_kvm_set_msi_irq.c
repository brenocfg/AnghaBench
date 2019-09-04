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
typedef  int u64 ;
struct kvm_lapic_irq {int dest_id; int vector; int dest_mode; int trig_mode; int delivery_mode; int msi_redir_hint; int level; scalar_t__ shorthand; } ;
struct TYPE_4__ {int address_lo; int data; scalar_t__ address_hi; } ;
struct kvm_kernel_irq_routing_entry {TYPE_2__ msi; } ;
struct TYPE_3__ {scalar_t__ x2apic_format; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSI_ADDR_DEST_ID_MASK ; 
 int MSI_ADDR_DEST_ID_SHIFT ; 
 int MSI_ADDR_DEST_MODE_SHIFT ; 
 int MSI_ADDR_EXT_DEST_ID (scalar_t__) ; 
 int MSI_ADDR_REDIRECTION_LOWPRI ; 
 int MSI_DATA_TRIGGER_SHIFT ; 
 int MSI_DATA_VECTOR_MASK ; 
 int MSI_DATA_VECTOR_SHIFT ; 
 int /*<<< orphan*/  trace_kvm_msi_set_irq (int,int) ; 

void kvm_set_msi_irq(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e,
		     struct kvm_lapic_irq *irq)
{
	trace_kvm_msi_set_irq(e->msi.address_lo | (kvm->arch.x2apic_format ?
	                                     (u64)e->msi.address_hi << 32 : 0),
	                      e->msi.data);

	irq->dest_id = (e->msi.address_lo &
			MSI_ADDR_DEST_ID_MASK) >> MSI_ADDR_DEST_ID_SHIFT;
	if (kvm->arch.x2apic_format)
		irq->dest_id |= MSI_ADDR_EXT_DEST_ID(e->msi.address_hi);
	irq->vector = (e->msi.data &
			MSI_DATA_VECTOR_MASK) >> MSI_DATA_VECTOR_SHIFT;
	irq->dest_mode = (1 << MSI_ADDR_DEST_MODE_SHIFT) & e->msi.address_lo;
	irq->trig_mode = (1 << MSI_DATA_TRIGGER_SHIFT) & e->msi.data;
	irq->delivery_mode = e->msi.data & 0x700;
	irq->msi_redir_hint = ((e->msi.address_lo
		& MSI_ADDR_REDIRECTION_LOWPRI) > 0);
	irq->level = 1;
	irq->shorthand = 0;
}