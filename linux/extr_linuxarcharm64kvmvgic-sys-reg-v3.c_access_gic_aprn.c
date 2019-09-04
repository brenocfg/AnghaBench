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
typedef  scalar_t__ u8 ;
struct sys_reg_params {scalar_t__ regval; int /*<<< orphan*/  is_write; } ;
struct sys_reg_desc {int Op2; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vgic_v3_access_apr_reg (struct kvm_vcpu*,struct sys_reg_params*,scalar_t__,scalar_t__) ; 
 scalar_t__ vgic_v3_max_apr_idx (struct kvm_vcpu*) ; 

__attribute__((used)) static bool access_gic_aprn(struct kvm_vcpu *vcpu, struct sys_reg_params *p,
			    const struct sys_reg_desc *r, u8 apr)
{
	u8 idx = r->Op2 & 3;

	if (idx > vgic_v3_max_apr_idx(vcpu))
		goto err;

	vgic_v3_access_apr_reg(vcpu, p, apr, idx);
	return true;
err:
	if (!p->is_write)
		p->regval = 0;

	return false;
}