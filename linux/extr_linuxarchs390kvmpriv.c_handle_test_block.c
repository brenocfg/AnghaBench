#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pgm; TYPE_3__* sie_block; } ;
struct TYPE_8__ {int /*<<< orphan*/  instruction_tb; } ;
struct kvm_vcpu {TYPE_7__* run; int /*<<< orphan*/  kvm; TYPE_4__ arch; TYPE_1__ stat; } ;
typedef  int gpa_t ;
struct TYPE_12__ {int* gprs; } ;
struct TYPE_13__ {TYPE_5__ regs; } ;
struct TYPE_14__ {TYPE_6__ s; } ;
struct TYPE_9__ {int mask; } ;
struct TYPE_10__ {TYPE_2__ gpsw; } ;

/* Variables and functions */
 int EFAULT ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PGM_ADDRESSING ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int PSW_MASK_PSTATE ; 
 scalar_t__ kvm_clear_guest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_error_gpa (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvm_s390_check_low_addr_prot_real (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_s390_get_regs_rre (struct kvm_vcpu*,int /*<<< orphan*/ *,int*) ; 
 int kvm_s390_inject_prog_irq (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_s390_logical_to_effective (struct kvm_vcpu*,int) ; 
 int kvm_s390_real_to_abs (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_test_block(struct kvm_vcpu *vcpu)
{
	gpa_t addr;
	int reg2;

	vcpu->stat.instruction_tb++;

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	kvm_s390_get_regs_rre(vcpu, NULL, &reg2);
	addr = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	addr = kvm_s390_logical_to_effective(vcpu, addr);
	if (kvm_s390_check_low_addr_prot_real(vcpu, addr))
		return kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);
	addr = kvm_s390_real_to_abs(vcpu, addr);

	if (kvm_is_error_gpa(vcpu->kvm, addr))
		return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);
	/*
	 * We don't expect errors on modern systems, and do not care
	 * about storage keys (yet), so let's just clear the page.
	 */
	if (kvm_clear_guest(vcpu->kvm, addr, PAGE_SIZE))
		return -EFAULT;
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->run->s.regs.gprs[0] = 0;
	return 0;
}