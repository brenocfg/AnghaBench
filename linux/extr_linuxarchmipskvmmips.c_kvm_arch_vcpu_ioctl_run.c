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
struct kvm_vcpu {int /*<<< orphan*/  mode; scalar_t__ mmio_needed; int /*<<< orphan*/  mmio_is_write; } ;
struct kvm_run {scalar_t__ immediate_exit; } ;
struct TYPE_2__ {int (* vcpu_run ) (struct kvm_run*,struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  IN_GUEST_MODE ; 
 int /*<<< orphan*/  guest_enter_irqoff () ; 
 int /*<<< orphan*/  guest_exit_irqoff () ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_mips_complete_mmio_load (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  kvm_sigset_activate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sigset_deactivate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lose_fpu (int) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_enter (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_out (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	int r = -EINTR;

	vcpu_load(vcpu);

	kvm_sigset_activate(vcpu);

	if (vcpu->mmio_needed) {
		if (!vcpu->mmio_is_write)
			kvm_mips_complete_mmio_load(vcpu, run);
		vcpu->mmio_needed = 0;
	}

	if (run->immediate_exit)
		goto out;

	lose_fpu(1);

	local_irq_disable();
	guest_enter_irqoff();
	trace_kvm_enter(vcpu);

	/*
	 * Make sure the read of VCPU requests in vcpu_run() callback is not
	 * reordered ahead of the write to vcpu->mode, or we could miss a TLB
	 * flush request while the requester sees the VCPU as outside of guest
	 * mode and not needing an IPI.
	 */
	smp_store_mb(vcpu->mode, IN_GUEST_MODE);

	r = kvm_mips_callbacks->vcpu_run(run, vcpu);

	trace_kvm_out(vcpu);
	guest_exit_irqoff();
	local_irq_enable();

out:
	kvm_sigset_deactivate(vcpu);

	vcpu_put(vcpu);
	return r;
}