#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u16 ;
struct TYPE_12__ {int pfault_token; int pfault_select; int pfault_compare; TYPE_1__* sie_block; } ;
struct TYPE_8__ {int /*<<< orphan*/  diagnose_258; } ;
struct kvm_vcpu {TYPE_6__ arch; TYPE_5__* run; int /*<<< orphan*/  kvm; TYPE_2__ stat; } ;
typedef  int /*<<< orphan*/  parm ;
struct TYPE_9__ {int* gprs; } ;
struct TYPE_10__ {TYPE_3__ regs; } ;
struct TYPE_11__ {TYPE_4__ s; } ;
struct TYPE_7__ {int ipa; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int KVM_S390_PFAULT_TOKEN_INVALID ; 
 int /*<<< orphan*/  PGM_ADDRESSING ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int,...) ; 
 int /*<<< orphan*/  kvm_is_error_gpa (int /*<<< orphan*/ ,int) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int read_guest (struct kvm_vcpu*,int,size_t,struct prs_parm*,int) ; 

__attribute__((used)) static int __diag_page_ref_service(struct kvm_vcpu *vcpu)
{
	struct prs_parm {
		u16 code;
		u16 subcode;
		u16 parm_len;
		u16 parm_version;
		u64 token_addr;
		u64 select_mask;
		u64 compare_mask;
		u64 zarch;
	};
	struct prs_parm parm;
	int rc;
	u16 rx = (vcpu->arch.sie_block->ipa & 0xf0) >> 4;
	u16 ry = (vcpu->arch.sie_block->ipa & 0x0f);

	VCPU_EVENT(vcpu, 3, "diag page reference parameter block at 0x%llx",
		   vcpu->run->s.regs.gprs[rx]);
	vcpu->stat.diagnose_258++;
	if (vcpu->run->s.regs.gprs[rx] & 7)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	rc = read_guest(vcpu, vcpu->run->s.regs.gprs[rx], rx, &parm, sizeof(parm));
	if (rc)
		return kvm_s390_inject_prog_cond(vcpu, rc);
	if (parm.parm_version != 2 || parm.parm_len < 5 || parm.code != 0x258)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	switch (parm.subcode) {
	case 0: /* TOKEN */
		VCPU_EVENT(vcpu, 3, "pageref token addr 0x%llx "
			   "select mask 0x%llx compare mask 0x%llx",
			   parm.token_addr, parm.select_mask, parm.compare_mask);
		if (vcpu->arch.pfault_token != KVM_S390_PFAULT_TOKEN_INVALID) {
			/*
			 * If the pagefault handshake is already activated,
			 * the token must not be changed.  We have to return
			 * decimal 8 instead, as mandated in SC24-6084.
			 */
			vcpu->run->s.regs.gprs[ry] = 8;
			return 0;
		}

		if ((parm.compare_mask & parm.select_mask) != parm.compare_mask ||
		    parm.token_addr & 7 || parm.zarch != 0x8000000000000000ULL)
			return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

		if (kvm_is_error_gpa(vcpu->kvm, parm.token_addr))
			return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);

		vcpu->arch.pfault_token = parm.token_addr;
		vcpu->arch.pfault_select = parm.select_mask;
		vcpu->arch.pfault_compare = parm.compare_mask;
		vcpu->run->s.regs.gprs[ry] = 0;
		rc = 0;
		break;
	case 1: /*
		 * CANCEL
		 * Specification allows to let already pending tokens survive
		 * the cancel, therefore to reduce code complexity, we assume
		 * all outstanding tokens are already pending.
		 */
		VCPU_EVENT(vcpu, 3, "pageref cancel addr 0x%llx", parm.token_addr);
		if (parm.token_addr || parm.select_mask ||
		    parm.compare_mask || parm.zarch)
			return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

		vcpu->run->s.regs.gprs[ry] = 0;
		/*
		 * If the pfault handling was not established or is already
		 * canceled SC24-6084 requests to return decimal 4.
		 */
		if (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
			vcpu->run->s.regs.gprs[ry] = 4;
		else
			vcpu->arch.pfault_token = KVM_S390_PFAULT_TOKEN_INVALID;

		rc = 0;
		break;
	default:
		rc = -EOPNOTSUPP;
		break;
	}

	return rc;
}