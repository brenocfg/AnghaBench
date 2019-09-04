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
typedef  int /*<<< orphan*/  u64 ;
struct sys_reg_params {int Op2; int /*<<< orphan*/  regval; int /*<<< orphan*/  is_write; } ;
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_pmu_v3_ready (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pmceid0_el0 ; 
 int /*<<< orphan*/  pmceid1_el0 ; 
 scalar_t__ pmu_access_el0_disabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 
 int trap_raz_wi (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 

__attribute__((used)) static bool access_pmceid(struct kvm_vcpu *vcpu, struct sys_reg_params *p,
			  const struct sys_reg_desc *r)
{
	u64 pmceid;

	if (!kvm_arm_pmu_v3_ready(vcpu))
		return trap_raz_wi(vcpu, p, r);

	BUG_ON(p->is_write);

	if (pmu_access_el0_disabled(vcpu))
		return false;

	if (!(p->Op2 & 1))
		pmceid = read_sysreg(pmceid0_el0);
	else
		pmceid = read_sysreg(pmceid1_el0);

	p->regval = pmceid;

	return true;
}