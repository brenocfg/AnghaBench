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
struct sys_reg_desc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sys_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  target; TYPE_1__ ctxt; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct sys_reg_desc const*) ; 
 size_t NR_SYS_REGS ; 
 scalar_t__ WARN (int,char*,size_t) ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,size_t) ; 
 struct sys_reg_desc* get_target_table (int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  reset_sys_reg_descs (struct kvm_vcpu*,struct sys_reg_desc const*,size_t) ; 
 struct sys_reg_desc const* sys_reg_descs ; 

void kvm_reset_sys_regs(struct kvm_vcpu *vcpu)
{
	size_t num;
	const struct sys_reg_desc *table;

	/* Catch someone adding a register without putting in reset entry. */
	memset(&vcpu->arch.ctxt.sys_regs, 0x42, sizeof(vcpu->arch.ctxt.sys_regs));

	/* Generic chip reset first (so target could override). */
	reset_sys_reg_descs(vcpu, sys_reg_descs, ARRAY_SIZE(sys_reg_descs));

	table = get_target_table(vcpu->arch.target, true, &num);
	reset_sys_reg_descs(vcpu, table, num);

	for (num = 1; num < NR_SYS_REGS; num++) {
		if (WARN(__vcpu_sys_reg(vcpu, num) == 0x4242424242424242,
			 "Didn't reset __vcpu_sys_reg(%zi)\n", num))
			break;
	}
}