#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sys_reg_params {int /*<<< orphan*/  regval; scalar_t__ is_write; } ;
struct sys_reg_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vgic_sre; } ;
struct TYPE_5__ {TYPE_1__ vgic_v3; } ;
struct TYPE_6__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int ignore_write (struct kvm_vcpu*,struct sys_reg_params*) ; 

__attribute__((used)) static bool access_gic_sre(struct kvm_vcpu *vcpu,
			   struct sys_reg_params *p,
			   const struct sys_reg_desc *r)
{
	if (p->is_write)
		return ignore_write(vcpu, p);

	p->regval = vcpu->arch.vgic_cpu.vgic_v3.vgic_sre;
	return true;
}