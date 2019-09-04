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
struct TYPE_2__ {int /*<<< orphan*/  hvc_exit_stat; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int kvm_hvc_call_handler (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_hvc_get_imm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_hvc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_reg (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int handle_hvc(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	int ret;

	trace_kvm_hvc(*vcpu_pc(vcpu), *vcpu_reg(vcpu, 0),
		      kvm_vcpu_hvc_get_imm(vcpu));
	vcpu->stat.hvc_exit_stat++;

	ret = kvm_hvc_call_handler(vcpu);
	if (ret < 0) {
		vcpu_set_reg(vcpu, 0, ~0UL);
		return 1;
	}

	return ret;
}