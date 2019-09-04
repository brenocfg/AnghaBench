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
typedef  scalar_t__ u64 ;
struct sys_reg_params {scalar_t__ regval; scalar_t__ is_write; } ;
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REG_ARM_PTIMER_CVAL ; 
 scalar_t__ kvm_arm_timer_get_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_timer_set_reg (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kvm_phys_timer_read () ; 

__attribute__((used)) static bool access_cntp_tval(struct kvm_vcpu *vcpu,
		struct sys_reg_params *p,
		const struct sys_reg_desc *r)
{
	u64 now = kvm_phys_timer_read();
	u64 cval;

	if (p->is_write) {
		kvm_arm_timer_set_reg(vcpu, KVM_REG_ARM_PTIMER_CVAL,
				      p->regval + now);
	} else {
		cval = kvm_arm_timer_get_reg(vcpu, KVM_REG_ARM_PTIMER_CVAL);
		p->regval = cval - now;
	}

	return true;
}