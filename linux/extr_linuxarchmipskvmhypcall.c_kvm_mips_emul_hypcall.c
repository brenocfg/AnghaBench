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
struct TYPE_3__ {int code; } ;
union mips_instruction {TYPE_1__ co_format; } ;
struct TYPE_4__ {int /*<<< orphan*/  pc; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_FAIL ; 
 int EMULATE_HYPERCALL ; 
 int /*<<< orphan*/  kvm_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 

enum emulation_result kvm_mips_emul_hypcall(struct kvm_vcpu *vcpu,
					    union mips_instruction inst)
{
	unsigned int code = (inst.co_format.code >> 5) & 0x3ff;

	kvm_debug("[%#lx] HYPCALL %#03x\n", vcpu->arch.pc, code);

	switch (code) {
	case 0:
		return EMULATE_HYPERCALL;
	default:
		return EMULATE_FAIL;
	};
}