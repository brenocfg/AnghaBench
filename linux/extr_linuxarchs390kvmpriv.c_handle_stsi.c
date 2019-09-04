#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_13__ {TYPE_3__* sie_block; } ;
struct TYPE_10__ {int /*<<< orphan*/  instruction_stsi; } ;
struct kvm_vcpu {TYPE_9__* run; TYPE_6__* kvm; TYPE_4__ arch; TYPE_1__ stat; } ;
struct TYPE_16__ {int* gprs; } ;
struct TYPE_17__ {TYPE_7__ regs; } ;
struct TYPE_18__ {TYPE_8__ s; } ;
struct TYPE_14__ {scalar_t__ user_stsi; } ;
struct TYPE_15__ {TYPE_5__ arch; } ;
struct TYPE_11__ {int mask; } ;
struct TYPE_12__ {TYPE_2__ gpsw; } ;

/* Variables and functions */
 int EREMOTE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_stsi_3_2_2 (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  insert_stsi_usr_data (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int kvm_s390_get_base_disp_s (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stsi (void*,int,int,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_stsi (struct kvm_vcpu*,int,int,int,int) ; 
 int write_guest (struct kvm_vcpu*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_stsi(struct kvm_vcpu *vcpu)
{
	int fc = (vcpu->run->s.regs.gprs[0] & 0xf0000000) >> 28;
	int sel1 = vcpu->run->s.regs.gprs[0] & 0xff;
	int sel2 = vcpu->run->s.regs.gprs[1] & 0xffff;
	unsigned long mem = 0;
	u64 operand2;
	int rc = 0;
	u8 ar;

	vcpu->stat.instruction_stsi++;
	VCPU_EVENT(vcpu, 3, "STSI: fc: %u sel1: %u sel2: %u", fc, sel1, sel2);

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	if (fc > 3) {
		kvm_s390_set_psw_cc(vcpu, 3);
		return 0;
	}

	if (vcpu->run->s.regs.gprs[0] & 0x0fffff00
	    || vcpu->run->s.regs.gprs[1] & 0xffff0000)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	if (fc == 0) {
		vcpu->run->s.regs.gprs[0] = 3 << 28;
		kvm_s390_set_psw_cc(vcpu, 0);
		return 0;
	}

	operand2 = kvm_s390_get_base_disp_s(vcpu, &ar);

	if (operand2 & 0xfff)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	switch (fc) {
	case 1: /* same handling for 1 and 2 */
	case 2:
		mem = get_zeroed_page(GFP_KERNEL);
		if (!mem)
			goto out_no_data;
		if (stsi((void *) mem, fc, sel1, sel2))
			goto out_no_data;
		break;
	case 3:
		if (sel1 != 2 || sel2 != 2)
			goto out_no_data;
		mem = get_zeroed_page(GFP_KERNEL);
		if (!mem)
			goto out_no_data;
		handle_stsi_3_2_2(vcpu, (void *) mem);
		break;
	}

	rc = write_guest(vcpu, operand2, ar, (void *)mem, PAGE_SIZE);
	if (rc) {
		rc = kvm_s390_inject_prog_cond(vcpu, rc);
		goto out;
	}
	if (vcpu->kvm->arch.user_stsi) {
		insert_stsi_usr_data(vcpu, operand2, ar, fc, sel1, sel2);
		rc = -EREMOTE;
	}
	trace_kvm_s390_handle_stsi(vcpu, fc, sel1, sel2, operand2);
	free_page(mem);
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->run->s.regs.gprs[0] = 0;
	return rc;
out_no_data:
	kvm_s390_set_psw_cc(vcpu, 3);
out:
	free_page(mem);
	return rc;
}