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
struct TYPE_3__ {int /*<<< orphan*/  cp15; } ;
struct TYPE_4__ {int /*<<< orphan*/  target; TYPE_1__ ctxt; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct coproc_reg {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct coproc_reg const*) ; 
 size_t NR_CP15_REGS ; 
 int /*<<< orphan*/  WARN (int,char*,size_t) ; 
 struct coproc_reg const* cp15_regs ; 
 struct coproc_reg* get_target_table (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reset_coproc_regs (struct kvm_vcpu*,struct coproc_reg const*,size_t) ; 
 int vcpu_cp15 (struct kvm_vcpu*,size_t) ; 

void kvm_reset_coprocs(struct kvm_vcpu *vcpu)
{
	size_t num;
	const struct coproc_reg *table;

	/* Catch someone adding a register without putting in reset entry. */
	memset(vcpu->arch.ctxt.cp15, 0x42, sizeof(vcpu->arch.ctxt.cp15));

	/* Generic chip reset first (so target could override). */
	reset_coproc_regs(vcpu, cp15_regs, ARRAY_SIZE(cp15_regs));

	table = get_target_table(vcpu->arch.target, &num);
	reset_coproc_regs(vcpu, table, num);

	for (num = 1; num < NR_CP15_REGS; num++)
		WARN(vcpu_cp15(vcpu, num) == 0x42424242,
		     "Didn't reset vcpu_cp15(vcpu, %zi)", num);
}