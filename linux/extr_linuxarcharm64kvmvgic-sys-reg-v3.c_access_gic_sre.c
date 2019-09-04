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
struct vgic_v3_cpu_if {int vgic_sre; } ;
struct sys_reg_params {int regval; scalar_t__ is_write; } ;
struct sys_reg_desc {int dummy; } ;
struct TYPE_3__ {struct vgic_v3_cpu_if vgic_v3; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int ICC_SRE_EL1_SRE ; 

__attribute__((used)) static bool access_gic_sre(struct kvm_vcpu *vcpu, struct sys_reg_params *p,
			   const struct sys_reg_desc *r)
{
	struct vgic_v3_cpu_if *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;

	/* Validate SRE bit */
	if (p->is_write) {
		if (!(p->regval & ICC_SRE_EL1_SRE))
			return false;
	} else {
		p->regval = vgicv3->vgic_sre;
	}

	return true;
}