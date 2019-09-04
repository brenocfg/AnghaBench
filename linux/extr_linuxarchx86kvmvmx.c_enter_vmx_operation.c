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
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct TYPE_3__ {int vmxon; int /*<<< orphan*/  vmcs02; void* cached_vmcs12; void* cached_shadow_vmcs12; int /*<<< orphan*/  vpid02; TYPE_2__ preemption_timer; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  VMCS12_SIZE ; 
 int alloc_loaded_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_shadow_vmcs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  allocate_vpid () ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  free_loaded_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_preemption_timer_fn ; 

__attribute__((used)) static int enter_vmx_operation(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int r;

	r = alloc_loaded_vmcs(&vmx->nested.vmcs02);
	if (r < 0)
		goto out_vmcs02;

	vmx->nested.cached_vmcs12 = kzalloc(VMCS12_SIZE, GFP_KERNEL);
	if (!vmx->nested.cached_vmcs12)
		goto out_cached_vmcs12;

	vmx->nested.cached_shadow_vmcs12 = kzalloc(VMCS12_SIZE, GFP_KERNEL);
	if (!vmx->nested.cached_shadow_vmcs12)
		goto out_cached_shadow_vmcs12;

	if (enable_shadow_vmcs && !alloc_shadow_vmcs(vcpu))
		goto out_shadow_vmcs;

	hrtimer_init(&vmx->nested.preemption_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_PINNED);
	vmx->nested.preemption_timer.function = vmx_preemption_timer_fn;

	vmx->nested.vpid02 = allocate_vpid();

	vmx->nested.vmxon = true;
	return 0;

out_shadow_vmcs:
	kfree(vmx->nested.cached_shadow_vmcs12);

out_cached_shadow_vmcs12:
	kfree(vmx->nested.cached_vmcs12);

out_cached_vmcs12:
	free_loaded_vmcs(&vmx->nested.vmcs02);

out_vmcs02:
	return -ENOMEM;
}