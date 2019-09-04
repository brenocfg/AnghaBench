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
struct kvm_vcpu_hv {int /*<<< orphan*/  vp_index; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vcpu_get_idx (struct kvm_vcpu*) ; 
 struct kvm_vcpu_hv* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

void kvm_hv_vcpu_postcreate(struct kvm_vcpu *vcpu)
{
	struct kvm_vcpu_hv *hv_vcpu = vcpu_to_hv_vcpu(vcpu);

	hv_vcpu->vp_index = kvm_vcpu_get_idx(vcpu);
}