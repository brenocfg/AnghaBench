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
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {scalar_t__ get_user; scalar_t__ reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int KVM_REG_ARM64_SYSREG ; 
 int KVM_REG_ARM_COPROC_MASK ; 
 struct sys_reg_desc* find_reg (struct sys_reg_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sys_reg_desc* find_reg_by_id (int,struct sys_reg_params*,struct sys_reg_desc const*,size_t) ; 
 struct sys_reg_desc* get_target_table (int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  sys_reg_descs ; 

__attribute__((used)) static const struct sys_reg_desc *index_to_sys_reg_desc(struct kvm_vcpu *vcpu,
						    u64 id)
{
	size_t num;
	const struct sys_reg_desc *table, *r;
	struct sys_reg_params params;

	/* We only do sys_reg for now. */
	if ((id & KVM_REG_ARM_COPROC_MASK) != KVM_REG_ARM64_SYSREG)
		return NULL;

	table = get_target_table(vcpu->arch.target, true, &num);
	r = find_reg_by_id(id, &params, table, num);
	if (!r)
		r = find_reg(&params, sys_reg_descs, ARRAY_SIZE(sys_reg_descs));

	/* Not saved in the sys_reg array and not otherwise accessible? */
	if (r && !(r->reg || r->get_user))
		r = NULL;

	return r;
}