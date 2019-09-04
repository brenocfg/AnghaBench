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
typedef  int /*<<< orphan*/  u8 ;
struct trans_exc_code_bits {int b61; int b56; int b60; unsigned long addr; int /*<<< orphan*/  as; int /*<<< orphan*/  fsi; } ;
struct kvm_s390_pgm_info {int code; int /*<<< orphan*/  exc_access_id; int /*<<< orphan*/  trans_exc_code; } ;
struct TYPE_5__ {TYPE_1__* sie_block; struct kvm_s390_pgm_info pgm; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  enum prot_type { ____Placeholder_prot_type } prot_type ;
typedef  enum gacc_mode { ____Placeholder_gacc_mode } gacc_mode ;
struct TYPE_6__ {int /*<<< orphan*/  as; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSI_FETCH ; 
 int /*<<< orphan*/  FSI_STORE ; 
 int GACC_STORE ; 
 unsigned long PAGE_SHIFT ; 
#define  PGM_ALEN_TRANSLATION 144 
#define  PGM_ALE_SEQUENCE 143 
#define  PGM_ASCE_TYPE 142 
#define  PGM_ASTE_SEQUENCE 141 
#define  PGM_ASTE_VALIDITY 140 
#define  PGM_EXTENDED_AUTHORITY 139 
#define  PGM_PAGE_TRANSLATION 138 
#define  PGM_PROTECTION 137 
#define  PGM_REGION_FIRST_TRANS 136 
#define  PGM_REGION_SECOND_TRANS 135 
#define  PGM_REGION_THIRD_TRANS 134 
#define  PGM_SEGMENT_TRANSLATION 133 
#define  PROT_TYPE_ALC 132 
#define  PROT_TYPE_DAT 131 
#define  PROT_TYPE_IEP 130 
#define  PROT_TYPE_KEYC 129 
#define  PROT_TYPE_LA 128 
 int /*<<< orphan*/  memset (struct kvm_s390_pgm_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ psw_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trans_exc(struct kvm_vcpu *vcpu, int code, unsigned long gva,
		     u8 ar, enum gacc_mode mode, enum prot_type prot)
{
	struct kvm_s390_pgm_info *pgm = &vcpu->arch.pgm;
	struct trans_exc_code_bits *tec;

	memset(pgm, 0, sizeof(*pgm));
	pgm->code = code;
	tec = (struct trans_exc_code_bits *)&pgm->trans_exc_code;

	switch (code) {
	case PGM_PROTECTION:
		switch (prot) {
		case PROT_TYPE_IEP:
			tec->b61 = 1;
			/* FALL THROUGH */
		case PROT_TYPE_LA:
			tec->b56 = 1;
			break;
		case PROT_TYPE_KEYC:
			tec->b60 = 1;
			break;
		case PROT_TYPE_ALC:
			tec->b60 = 1;
			/* FALL THROUGH */
		case PROT_TYPE_DAT:
			tec->b61 = 1;
			break;
		}
		/* FALL THROUGH */
	case PGM_ASCE_TYPE:
	case PGM_PAGE_TRANSLATION:
	case PGM_REGION_FIRST_TRANS:
	case PGM_REGION_SECOND_TRANS:
	case PGM_REGION_THIRD_TRANS:
	case PGM_SEGMENT_TRANSLATION:
		/*
		 * op_access_id only applies to MOVE_PAGE -> set bit 61
		 * exc_access_id has to be set to 0 for some instructions. Both
		 * cases have to be handled by the caller.
		 */
		tec->addr = gva >> PAGE_SHIFT;
		tec->fsi = mode == GACC_STORE ? FSI_STORE : FSI_FETCH;
		tec->as = psw_bits(vcpu->arch.sie_block->gpsw).as;
		/* FALL THROUGH */
	case PGM_ALEN_TRANSLATION:
	case PGM_ALE_SEQUENCE:
	case PGM_ASTE_VALIDITY:
	case PGM_ASTE_SEQUENCE:
	case PGM_EXTENDED_AUTHORITY:
		/*
		 * We can always store exc_access_id, as it is
		 * undefined for non-ar cases. It is undefined for
		 * most DAT protection exceptions.
		 */
		pgm->exc_access_id = ar;
		break;
	}
	return code;
}