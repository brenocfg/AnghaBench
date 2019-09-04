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
typedef  int u32 ;
struct TYPE_14__ {TYPE_6__* sie_block; } ;
struct TYPE_11__ {int /*<<< orphan*/  instruction_sckpf; } ;
struct kvm_vcpu {TYPE_7__ arch; TYPE_3__* run; TYPE_4__ stat; } ;
struct TYPE_12__ {int mask; } ;
struct TYPE_13__ {int todpr; TYPE_5__ gpsw; } ;
struct TYPE_8__ {int* gprs; } ;
struct TYPE_9__ {TYPE_1__ regs; } ;
struct TYPE_10__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW_MASK_PSTATE ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_sckpf(struct kvm_vcpu *vcpu)
{
	u32 value;

	vcpu->stat.instruction_sckpf++;

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	if (vcpu->run->s.regs.gprs[0] & 0x00000000ffff0000)
		return kvm_s390_inject_program_int(vcpu,
						   PGM_SPECIFICATION);

	value = vcpu->run->s.regs.gprs[0] & 0x000000000000ffff;
	vcpu->arch.sie_block->todpr = value;

	return 0;
}