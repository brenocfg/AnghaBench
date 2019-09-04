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
struct kvm_vcpu_hv {int /*<<< orphan*/ * stimer; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stimer_cleanup (int /*<<< orphan*/ *) ; 
 struct kvm_vcpu_hv* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

void kvm_hv_vcpu_uninit(struct kvm_vcpu *vcpu)
{
	struct kvm_vcpu_hv *hv_vcpu = vcpu_to_hv_vcpu(vcpu);
	int i;

	for (i = 0; i < ARRAY_SIZE(hv_vcpu->stimer); i++)
		stimer_cleanup(&hv_vcpu->stimer[i]);
}