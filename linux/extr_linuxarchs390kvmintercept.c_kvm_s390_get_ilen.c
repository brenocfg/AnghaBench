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
typedef  int u8 ;
struct TYPE_2__ {struct kvm_s390_sie_block* sie_block; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_s390_sie_block {int icptcode; int ipa; int icptstatus; int pgmilc; } ;

/* Variables and functions */
#define  ICPT_INST 133 
#define  ICPT_INSTPROGI 132 
#define  ICPT_IOINST 131 
#define  ICPT_OPEREXC 130 
#define  ICPT_PARTEXEC 129 
#define  ICPT_PROGI 128 
 int insn_length (int) ; 

u8 kvm_s390_get_ilen(struct kvm_vcpu *vcpu)
{
	struct kvm_s390_sie_block *sie_block = vcpu->arch.sie_block;
	u8 ilen = 0;

	switch (vcpu->arch.sie_block->icptcode) {
	case ICPT_INST:
	case ICPT_INSTPROGI:
	case ICPT_OPEREXC:
	case ICPT_PARTEXEC:
	case ICPT_IOINST:
		/* instruction only stored for these icptcodes */
		ilen = insn_length(vcpu->arch.sie_block->ipa >> 8);
		/* Use the length of the EXECUTE instruction if necessary */
		if (sie_block->icptstatus & 1) {
			ilen = (sie_block->icptstatus >> 4) & 0x6;
			if (!ilen)
				ilen = 4;
		}
		break;
	case ICPT_PROGI:
		/* bit 1+2 of pgmilc are the ilc, so we directly get ilen */
		ilen = vcpu->arch.sie_block->pgmilc & 0x6;
		break;
	}
	return ilen;
}