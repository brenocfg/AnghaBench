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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  hypercalls; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_hv_hypercall_set_result (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_hv_hypercall_complete(struct kvm_vcpu *vcpu, u64 result)
{
	kvm_hv_hypercall_set_result(vcpu, result);
	++vcpu->stat.hypercalls;
	return kvm_skip_emulated_instruction(vcpu);
}