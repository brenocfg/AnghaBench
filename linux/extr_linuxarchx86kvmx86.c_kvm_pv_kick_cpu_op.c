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
struct kvm_lapic_irq {int dest_id; int msi_redir_hint; int /*<<< orphan*/  delivery_mode; scalar_t__ level; scalar_t__ dest_mode; scalar_t__ shorthand; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_REMRD ; 
 int /*<<< orphan*/  kvm_irq_delivery_to_apic (struct kvm*,int /*<<< orphan*/ *,struct kvm_lapic_irq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_pv_kick_cpu_op(struct kvm *kvm, unsigned long flags, int apicid)
{
	struct kvm_lapic_irq lapic_irq;

	lapic_irq.shorthand = 0;
	lapic_irq.dest_mode = 0;
	lapic_irq.level = 0;
	lapic_irq.dest_id = apicid;
	lapic_irq.msi_redir_hint = false;

	lapic_irq.delivery_mode = APIC_DM_REMRD;
	kvm_irq_delivery_to_apic(kvm, NULL, &lapic_irq, NULL);
}