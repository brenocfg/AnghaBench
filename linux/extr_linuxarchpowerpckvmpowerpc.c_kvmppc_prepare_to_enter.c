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
struct kvm_vcpu {int /*<<< orphan*/  mode; TYPE_1__* run; } ;
struct TYPE_2__ {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  IN_GUEST_MODE ; 
 int /*<<< orphan*/  KVM_EXIT_INTR ; 
 int /*<<< orphan*/  SIGNAL_EXITS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  guest_enter_irqoff () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ kvm_request_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_account_exit (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_core_check_requests (struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_core_prepare_to_enter (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  trace_kvm_check_requests (struct kvm_vcpu*) ; 

int kvmppc_prepare_to_enter(struct kvm_vcpu *vcpu)
{
	int r;

	WARN_ON(irqs_disabled());
	hard_irq_disable();

	while (true) {
		if (need_resched()) {
			local_irq_enable();
			cond_resched();
			hard_irq_disable();
			continue;
		}

		if (signal_pending(current)) {
			kvmppc_account_exit(vcpu, SIGNAL_EXITS);
			vcpu->run->exit_reason = KVM_EXIT_INTR;
			r = -EINTR;
			break;
		}

		vcpu->mode = IN_GUEST_MODE;

		/*
		 * Reading vcpu->requests must happen after setting vcpu->mode,
		 * so we don't miss a request because the requester sees
		 * OUTSIDE_GUEST_MODE and assumes we'll be checking requests
		 * before next entering the guest (and thus doesn't IPI).
		 * This also orders the write to mode from any reads
		 * to the page tables done while the VCPU is running.
		 * Please see the comment in kvm_flush_remote_tlbs.
		 */
		smp_mb();

		if (kvm_request_pending(vcpu)) {
			/* Make sure we process requests preemptable */
			local_irq_enable();
			trace_kvm_check_requests(vcpu);
			r = kvmppc_core_check_requests(vcpu);
			hard_irq_disable();
			if (r > 0)
				continue;
			break;
		}

		if (kvmppc_core_prepare_to_enter(vcpu)) {
			/* interrupts got enabled in between, so we
			   are back at square 1 */
			continue;
		}

		guest_enter_irqoff();
		return 1;
	}

	/* return to host */
	local_irq_enable();
	return r;
}