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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_s390_pgm_info {int code; int /*<<< orphan*/  per_access_id; int /*<<< orphan*/  per_address; int /*<<< orphan*/  per_atmid; int /*<<< orphan*/  per_code; int /*<<< orphan*/  exc_access_id; int /*<<< orphan*/  trans_exc_code; int /*<<< orphan*/  data_exc_code; int /*<<< orphan*/  mon_code; int /*<<< orphan*/  mon_class_nr; int /*<<< orphan*/  op_access_id; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int iprcc; int /*<<< orphan*/  peraid; int /*<<< orphan*/  peraddr; int /*<<< orphan*/  peratmid; int /*<<< orphan*/  perc; int /*<<< orphan*/  eai; int /*<<< orphan*/  tecmc; int /*<<< orphan*/  dxc; int /*<<< orphan*/  mcn; int /*<<< orphan*/  oai; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_PGM_FLAGS_NO_REWIND ; 
#define  PGM_AFX_TRANSLATION 153 
#define  PGM_ALEN_TRANSLATION 152 
#define  PGM_ALE_SEQUENCE 151 
#define  PGM_ASCE_TYPE 150 
#define  PGM_ASTE_INSTANCE 149 
#define  PGM_ASTE_SEQUENCE 148 
#define  PGM_ASTE_VALIDITY 147 
#define  PGM_ASX_TRANSLATION 146 
#define  PGM_DATA 145 
#define  PGM_EXTENDED_AUTHORITY 144 
#define  PGM_EX_TRANSLATION 143 
#define  PGM_LFX_TRANSLATION 142 
#define  PGM_LSTE_SEQUENCE 141 
#define  PGM_LSX_TRANSLATION 140 
#define  PGM_LX_TRANSLATION 139 
#define  PGM_MONITOR 138 
#define  PGM_PAGE_TRANSLATION 137 
 int PGM_PER ; 
#define  PGM_PRIMARY_AUTHORITY 136 
#define  PGM_PROTECTION 135 
#define  PGM_REGION_FIRST_TRANS 134 
#define  PGM_REGION_SECOND_TRANS 133 
#define  PGM_REGION_THIRD_TRANS 132 
#define  PGM_SECONDARY_AUTHORITY 131 
#define  PGM_SEGMENT_TRANSLATION 130 
#define  PGM_SPACE_SWITCH 129 
#define  PGM_VECTOR_PROCESSING 128 
 int kvm_s390_inject_prog_irq (struct kvm_vcpu*,struct kvm_s390_pgm_info*) ; 

__attribute__((used)) static int inject_prog_on_prog_intercept(struct kvm_vcpu *vcpu)
{
	struct kvm_s390_pgm_info pgm_info = {
		.code = vcpu->arch.sie_block->iprcc,
		/* the PSW has already been rewound */
		.flags = KVM_S390_PGM_FLAGS_NO_REWIND,
	};

	switch (vcpu->arch.sie_block->iprcc & ~PGM_PER) {
	case PGM_AFX_TRANSLATION:
	case PGM_ASX_TRANSLATION:
	case PGM_EX_TRANSLATION:
	case PGM_LFX_TRANSLATION:
	case PGM_LSTE_SEQUENCE:
	case PGM_LSX_TRANSLATION:
	case PGM_LX_TRANSLATION:
	case PGM_PRIMARY_AUTHORITY:
	case PGM_SECONDARY_AUTHORITY:
	case PGM_SPACE_SWITCH:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		break;
	case PGM_ALEN_TRANSLATION:
	case PGM_ALE_SEQUENCE:
	case PGM_ASTE_INSTANCE:
	case PGM_ASTE_SEQUENCE:
	case PGM_ASTE_VALIDITY:
	case PGM_EXTENDED_AUTHORITY:
		pgm_info.exc_access_id = vcpu->arch.sie_block->eai;
		break;
	case PGM_ASCE_TYPE:
	case PGM_PAGE_TRANSLATION:
	case PGM_REGION_FIRST_TRANS:
	case PGM_REGION_SECOND_TRANS:
	case PGM_REGION_THIRD_TRANS:
	case PGM_SEGMENT_TRANSLATION:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		pgm_info.exc_access_id  = vcpu->arch.sie_block->eai;
		pgm_info.op_access_id  = vcpu->arch.sie_block->oai;
		break;
	case PGM_MONITOR:
		pgm_info.mon_class_nr = vcpu->arch.sie_block->mcn;
		pgm_info.mon_code = vcpu->arch.sie_block->tecmc;
		break;
	case PGM_VECTOR_PROCESSING:
	case PGM_DATA:
		pgm_info.data_exc_code = vcpu->arch.sie_block->dxc;
		break;
	case PGM_PROTECTION:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		pgm_info.exc_access_id  = vcpu->arch.sie_block->eai;
		break;
	default:
		break;
	}

	if (vcpu->arch.sie_block->iprcc & PGM_PER) {
		pgm_info.per_code = vcpu->arch.sie_block->perc;
		pgm_info.per_atmid = vcpu->arch.sie_block->peratmid;
		pgm_info.per_address = vcpu->arch.sie_block->peraddr;
		pgm_info.per_access_id = vcpu->arch.sie_block->peraid;
	}
	return kvm_s390_inject_prog_irq(vcpu, &pgm_info);
}