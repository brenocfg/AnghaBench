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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_lapic {TYPE_1__* vcpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LDR ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_apic_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void kvm_apic_set_ldr(struct kvm_lapic *apic, u32 id)
{
	kvm_lapic_set_reg(apic, APIC_LDR, id);
	recalculate_apic_map(apic->vcpu->kvm);
}