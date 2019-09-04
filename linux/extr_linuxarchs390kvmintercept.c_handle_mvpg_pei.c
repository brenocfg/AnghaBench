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
struct kvm_vcpu {TYPE_3__* run; } ;
struct TYPE_4__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
struct TYPE_6__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  GACC_FETCH ; 
 int /*<<< orphan*/  GACC_STORE ; 
 int guest_translate_address (struct kvm_vcpu*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int kvm_arch_fault_in_page (struct kvm_vcpu*,unsigned long,int) ; 
 int /*<<< orphan*/  kvm_s390_get_regs_rre (struct kvm_vcpu*,int*,int*) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_s390_retry_instr (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_mvpg_pei(struct kvm_vcpu *vcpu)
{
	unsigned long srcaddr, dstaddr;
	int reg1, reg2, rc;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	/* Make sure that the source is paged-in */
	rc = guest_translate_address(vcpu, vcpu->run->s.regs.gprs[reg2],
				     reg2, &srcaddr, GACC_FETCH);
	if (rc)
		return kvm_s390_inject_prog_cond(vcpu, rc);
	rc = kvm_arch_fault_in_page(vcpu, srcaddr, 0);
	if (rc != 0)
		return rc;

	/* Make sure that the destination is paged-in */
	rc = guest_translate_address(vcpu, vcpu->run->s.regs.gprs[reg1],
				     reg1, &dstaddr, GACC_STORE);
	if (rc)
		return kvm_s390_inject_prog_cond(vcpu, rc);
	rc = kvm_arch_fault_in_page(vcpu, dstaddr, 1);
	if (rc != 0)
		return rc;

	kvm_s390_retry_instr(vcpu);

	return 0;
}