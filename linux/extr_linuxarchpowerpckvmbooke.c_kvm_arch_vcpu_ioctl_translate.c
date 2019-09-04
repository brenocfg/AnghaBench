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
struct kvm_vcpu {int dummy; } ;
struct kvm_translation {int dummy; } ;

/* Variables and functions */
 int kvmppc_core_vcpu_translate (struct kvm_vcpu*,struct kvm_translation*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu,
                                  struct kvm_translation *tr)
{
	int r;

	vcpu_load(vcpu);
	r = kvmppc_core_vcpu_translate(vcpu, tr);
	vcpu_put(vcpu);
	return r;
}