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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct coproc_reg {int /*<<< orphan*/  reg; } ;
struct coproc_params {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct coproc_reg const*) ; 
 int KVM_REG_ARM_COPROC_MASK ; 
 int KVM_REG_ARM_COPROC_SHIFT ; 
 struct coproc_reg const* cp15_regs ; 
 struct coproc_reg* find_reg (struct coproc_params*,struct coproc_reg const*,size_t) ; 
 struct coproc_reg* get_target_table (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  index_to_params (int,struct coproc_params*) ; 

__attribute__((used)) static const struct coproc_reg *index_to_coproc_reg(struct kvm_vcpu *vcpu,
						    u64 id)
{
	size_t num;
	const struct coproc_reg *table, *r;
	struct coproc_params params;

	/* We only do cp15 for now. */
	if ((id & KVM_REG_ARM_COPROC_MASK) >> KVM_REG_ARM_COPROC_SHIFT != 15)
		return NULL;

	if (!index_to_params(id, &params))
		return NULL;

	table = get_target_table(vcpu->arch.target, &num);
	r = find_reg(&params, table, num);
	if (!r)
		r = find_reg(&params, cp15_regs, ARRAY_SIZE(cp15_regs));

	/* Not saved in the cp15 array? */
	if (r && !r->reg)
		r = NULL;

	return r;
}