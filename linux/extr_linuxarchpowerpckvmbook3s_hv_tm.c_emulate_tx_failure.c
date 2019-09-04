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
struct TYPE_5__ {int msr; } ;
struct TYPE_4__ {int nip; } ;
struct TYPE_6__ {int tfiar; int texasr; TYPE_2__ shregs; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int MSR_PR ; 
 scalar_t__ MSR_TM_SUSPENDED (int) ; 
 int TEXASR_ABORT ; 
 int TEXASR_EXACT ; 
 int TEXASR_FS ; 
 int TEXASR_PR ; 
 int TEXASR_SUSP ; 

__attribute__((used)) static void emulate_tx_failure(struct kvm_vcpu *vcpu, u64 failure_cause)
{
	u64 texasr, tfiar;
	u64 msr = vcpu->arch.shregs.msr;

	tfiar = vcpu->arch.regs.nip & ~0x3ull;
	texasr = (failure_cause << 56) | TEXASR_ABORT | TEXASR_FS | TEXASR_EXACT;
	if (MSR_TM_SUSPENDED(vcpu->arch.shregs.msr))
		texasr |= TEXASR_SUSP;
	if (msr & MSR_PR) {
		texasr |= TEXASR_PR;
		tfiar |= 1;
	}
	vcpu->arch.tfiar = tfiar;
	/* Preserve ROT and TL fields of existing TEXASR */
	vcpu->arch.texasr = (vcpu->arch.texasr & 0x3ffffff) | texasr;
}