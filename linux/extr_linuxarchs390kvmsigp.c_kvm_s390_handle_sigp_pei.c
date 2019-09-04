#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_5__* run; TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_9__ {TYPE_3__ regs; } ;
struct TYPE_10__ {TYPE_4__ s; } ;
struct TYPE_6__ {int ipa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SIGP_CC_ORDER_CODE_ACCEPTED ; 
 scalar_t__ SIGP_EXTERNAL_CALL ; 
 struct kvm_vcpu* kvm_get_vcpu_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_s390_get_base_disp_rs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_wakeup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_sigp_pei (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ ) ; 

int kvm_s390_handle_sigp_pei(struct kvm_vcpu *vcpu)
{
	int r3 = vcpu->arch.sie_block->ipa & 0x000f;
	u16 cpu_addr = vcpu->run->s.regs.gprs[r3];
	struct kvm_vcpu *dest_vcpu;
	u8 order_code = kvm_s390_get_base_disp_rs(vcpu, NULL);

	trace_kvm_s390_handle_sigp_pei(vcpu, order_code, cpu_addr);

	if (order_code == SIGP_EXTERNAL_CALL) {
		dest_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, cpu_addr);
		BUG_ON(dest_vcpu == NULL);

		kvm_s390_vcpu_wakeup(dest_vcpu);
		kvm_s390_set_psw_cc(vcpu, SIGP_CC_ORDER_CODE_ACCEPTED);
		return 0;
	}

	return -EOPNOTSUPP;
}