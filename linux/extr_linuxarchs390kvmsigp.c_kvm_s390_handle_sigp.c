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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_11__ {int /*<<< orphan*/  instruction_sigp_arch; } ;
struct TYPE_10__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_7__* run; TYPE_4__ stat; TYPE_3__ arch; } ;
struct TYPE_12__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_13__ {TYPE_5__ regs; } ;
struct TYPE_14__ {TYPE_6__ s; } ;
struct TYPE_8__ {int mask; } ;
struct TYPE_9__ {int ipa; TYPE_1__ gpsw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int PSW_MASK_PSTATE ; 
#define  SIGP_SET_ARCHITECTURE 128 
 int __sigp_set_arch (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int handle_sigp_dst (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_sigp_order_in_user_space (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int kvm_s390_get_base_disp_rs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_sigp (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_s390_handle_sigp(struct kvm_vcpu *vcpu)
{
	int r1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	int r3 = vcpu->arch.sie_block->ipa & 0x000f;
	u32 parameter;
	u16 cpu_addr = vcpu->run->s.regs.gprs[r3];
	u8 order_code;
	int rc;

	/* sigp in userspace can exit */
	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	order_code = kvm_s390_get_base_disp_rs(vcpu, NULL);
	if (handle_sigp_order_in_user_space(vcpu, order_code, cpu_addr))
		return -EOPNOTSUPP;

	if (r1 % 2)
		parameter = vcpu->run->s.regs.gprs[r1];
	else
		parameter = vcpu->run->s.regs.gprs[r1 + 1];

	trace_kvm_s390_handle_sigp(vcpu, order_code, cpu_addr, parameter);
	switch (order_code) {
	case SIGP_SET_ARCHITECTURE:
		vcpu->stat.instruction_sigp_arch++;
		rc = __sigp_set_arch(vcpu, parameter,
				     &vcpu->run->s.regs.gprs[r1]);
		break;
	default:
		rc = handle_sigp_dst(vcpu, order_code, cpu_addr,
				     parameter,
				     &vcpu->run->s.regs.gprs[r1]);
	}

	if (rc < 0)
		return rc;

	kvm_s390_set_psw_cc(vcpu, rc);
	return 0;
}