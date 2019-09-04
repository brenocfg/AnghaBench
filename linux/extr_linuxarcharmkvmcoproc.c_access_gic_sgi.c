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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct coproc_reg {int dummy; } ;
struct coproc_params {int Op1; int /*<<< orphan*/  Rt1; int /*<<< orphan*/  Rt2; int /*<<< orphan*/  is_write; } ;

/* Variables and functions */
 int read_from_write_only (struct kvm_vcpu*,struct coproc_params const*) ; 
 int* vcpu_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_v3_dispatch_sgi (struct kvm_vcpu*,int,int) ; 

__attribute__((used)) static bool access_gic_sgi(struct kvm_vcpu *vcpu,
			   const struct coproc_params *p,
			   const struct coproc_reg *r)
{
	u64 reg;
	bool g1;

	if (!p->is_write)
		return read_from_write_only(vcpu, p);

	reg = (u64)*vcpu_reg(vcpu, p->Rt2) << 32;
	reg |= *vcpu_reg(vcpu, p->Rt1) ;

	/*
	 * In a system where GICD_CTLR.DS=1, a ICC_SGI0R access generates
	 * Group0 SGIs only, while ICC_SGI1R can generate either group,
	 * depending on the SGI configuration. ICC_ASGI1R is effectively
	 * equivalent to ICC_SGI0R, as there is no "alternative" secure
	 * group.
	 */
	switch (p->Op1) {
	default:		/* Keep GCC quiet */
	case 0:			/* ICC_SGI1R */
		g1 = true;
		break;
	case 1:			/* ICC_ASGI1R */
	case 2:			/* ICC_SGI0R */
		g1 = false;
		break;
	}

	vgic_v3_dispatch_sgi(vcpu, reg, g1);

	return true;
}