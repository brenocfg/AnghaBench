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
struct TYPE_6__ {int vector; int trig_mode; int /*<<< orphan*/  mask; scalar_t__ remote_irr; } ;
union kvm_ioapic_redirect_entry {int /*<<< orphan*/  bits; TYPE_3__ fields; } ;
struct TYPE_5__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {size_t vcpu_id; TYPE_2__ arch; } ;
struct kvm_lapic {int dummy; } ;
struct dest_map {int* vectors; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {struct dest_map dest_map; } ;
struct kvm_ioapic {int irr; scalar_t__* irq_eoi; int /*<<< orphan*/  eoi_inject; int /*<<< orphan*/  lock; int /*<<< orphan*/  kvm; union kvm_ioapic_redirect_entry* redirtbl; TYPE_1__ rtc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_SPIV ; 
 int APIC_SPIV_DIRECTED_EOI ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int HZ ; 
 int IOAPIC_LEVEL_TRIG ; 
 int IOAPIC_NUM_PINS ; 
 scalar_t__ IOAPIC_SUCCESSIVE_IRQ_MAX_COUNT ; 
 int /*<<< orphan*/  KVM_IRQCHIP_IOAPIC ; 
 int /*<<< orphan*/  ioapic_service (struct kvm_ioapic*,int,int) ; 
 int kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_notify_acked_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_irq_eoi (struct kvm_ioapic*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_ioapic_delayed_eoi_inj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __kvm_ioapic_update_eoi(struct kvm_vcpu *vcpu,
			struct kvm_ioapic *ioapic, int vector, int trigger_mode)
{
	struct dest_map *dest_map = &ioapic->rtc_status.dest_map;
	struct kvm_lapic *apic = vcpu->arch.apic;
	int i;

	/* RTC special handling */
	if (test_bit(vcpu->vcpu_id, dest_map->map) &&
	    vector == dest_map->vectors[vcpu->vcpu_id])
		rtc_irq_eoi(ioapic, vcpu);

	for (i = 0; i < IOAPIC_NUM_PINS; i++) {
		union kvm_ioapic_redirect_entry *ent = &ioapic->redirtbl[i];

		if (ent->fields.vector != vector)
			continue;

		/*
		 * We are dropping lock while calling ack notifiers because ack
		 * notifier callbacks for assigned devices call into IOAPIC
		 * recursively. Since remote_irr is cleared only after call
		 * to notifiers if the same vector will be delivered while lock
		 * is dropped it will be put into irr and will be delivered
		 * after ack notifier returns.
		 */
		spin_unlock(&ioapic->lock);
		kvm_notify_acked_irq(ioapic->kvm, KVM_IRQCHIP_IOAPIC, i);
		spin_lock(&ioapic->lock);

		if (trigger_mode != IOAPIC_LEVEL_TRIG ||
		    kvm_lapic_get_reg(apic, APIC_SPIV) & APIC_SPIV_DIRECTED_EOI)
			continue;

		ASSERT(ent->fields.trig_mode == IOAPIC_LEVEL_TRIG);
		ent->fields.remote_irr = 0;
		if (!ent->fields.mask && (ioapic->irr & (1 << i))) {
			++ioapic->irq_eoi[i];
			if (ioapic->irq_eoi[i] == IOAPIC_SUCCESSIVE_IRQ_MAX_COUNT) {
				/*
				 * Real hardware does not deliver the interrupt
				 * immediately during eoi broadcast, and this
				 * lets a buggy guest make slow progress
				 * even if it does not correctly handle a
				 * level-triggered interrupt.  Emulate this
				 * behavior if we detect an interrupt storm.
				 */
				schedule_delayed_work(&ioapic->eoi_inject, HZ / 100);
				ioapic->irq_eoi[i] = 0;
				trace_kvm_ioapic_delayed_eoi_inj(ent->bits);
			} else {
				ioapic_service(ioapic, i, false);
			}
		} else {
			ioapic->irq_eoi[i] = 0;
		}
	}
}