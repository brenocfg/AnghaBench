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
typedef  int u64 ;
typedef  int u16 ;
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int const mask; scalar_t__ addr; } ;
typedef  TYPE_3__ psw_t ;
struct TYPE_4__ {int* gcr; TYPE_3__ gpsw; } ;

/* Variables and functions */
 int PSW_MASK_EXT ; 
 int PSW_MASK_IO ; 
 int SIGP_CC_STATUS_STORED ; 
 int SIGP_STATUS_INCORRECT_STATE ; 
 int __inject_sigp_emergency (struct kvm_vcpu*,struct kvm_vcpu*) ; 
 int is_vcpu_idle (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_vcpu_stopped (struct kvm_vcpu*) ; 

__attribute__((used)) static int __sigp_conditional_emergency(struct kvm_vcpu *vcpu,
					struct kvm_vcpu *dst_vcpu,
					u16 asn, u64 *reg)
{
	const u64 psw_int_mask = PSW_MASK_IO | PSW_MASK_EXT;
	u16 p_asn, s_asn;
	psw_t *psw;
	bool idle;

	idle = is_vcpu_idle(vcpu);
	psw = &dst_vcpu->arch.sie_block->gpsw;
	p_asn = dst_vcpu->arch.sie_block->gcr[4] & 0xffff;  /* Primary ASN */
	s_asn = dst_vcpu->arch.sie_block->gcr[3] & 0xffff;  /* Secondary ASN */

	/* Inject the emergency signal? */
	if (!is_vcpu_stopped(vcpu)
	    || (psw->mask & psw_int_mask) != psw_int_mask
	    || (idle && psw->addr != 0)
	    || (!idle && (asn == p_asn || asn == s_asn))) {
		return __inject_sigp_emergency(vcpu, dst_vcpu);
	} else {
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INCORRECT_STATE;
		return SIGP_CC_STATUS_STORED;
	}
}