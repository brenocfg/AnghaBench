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
struct kvm_vcpu {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTSIDE_GUEST_MODE ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void kvm_trap_emul_gva_lockless_end(struct kvm_vcpu *vcpu)
{
	/*
	 * Make sure the write to vcpu->mode is not reordered in front of GVA
	 * accesses, or a TLB flush requester may not think it necessary to send
	 * an IPI.
	 */
	smp_store_release(&vcpu->mode, OUTSIDE_GUEST_MODE);

	/*
	 * Now that the access to GVA space is complete, its safe for pending
	 * TLB flush request IPIs to be handled (which indicates completion).
	 */
	local_irq_enable();
}