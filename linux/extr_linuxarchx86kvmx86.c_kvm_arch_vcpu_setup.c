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
struct TYPE_2__ {int /*<<< orphan*/  arch_capabilities; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_get_arch_capabilities () ; 
 int /*<<< orphan*/  kvm_mmu_setup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_mtrr_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_reset (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
{
	vcpu->arch.arch_capabilities = kvm_get_arch_capabilities();
	kvm_vcpu_mtrr_init(vcpu);
	vcpu_load(vcpu);
	kvm_vcpu_reset(vcpu, false);
	kvm_mmu_setup(vcpu);
	vcpu_put(vcpu);
	return 0;
}