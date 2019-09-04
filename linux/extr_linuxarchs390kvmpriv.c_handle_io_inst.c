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
struct TYPE_7__ {int /*<<< orphan*/  instruction_io_other; } ;
struct TYPE_9__ {TYPE_6__* sie_block; } ;
struct kvm_vcpu {TYPE_1__ stat; TYPE_3__ arch; TYPE_5__* kvm; } ;
struct TYPE_8__ {int mask; } ;
struct TYPE_12__ {int ipa; TYPE_2__ gpsw; } ;
struct TYPE_10__ {scalar_t__ css_support; } ;
struct TYPE_11__ {TYPE_4__ arch; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int handle_tpi (struct kvm_vcpu*) ; 
 int handle_tsch (struct kvm_vcpu*) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int handle_io_inst(struct kvm_vcpu *vcpu)
{
	VCPU_EVENT(vcpu, 4, "%s", "I/O instruction");

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	if (vcpu->kvm->arch.css_support) {
		/*
		 * Most I/O instructions will be handled by userspace.
		 * Exceptions are tpi and the interrupt portion of tsch.
		 */
		if (vcpu->arch.sie_block->ipa == 0xb236)
			return handle_tpi(vcpu);
		if (vcpu->arch.sie_block->ipa == 0xb235)
			return handle_tsch(vcpu);
		/* Handle in userspace. */
		vcpu->stat.instruction_io_other++;
		return -EOPNOTSUPP;
	} else {
		/*
		 * Set condition code 3 to stop the guest from issuing channel
		 * I/O instructions.
		 */
		kvm_s390_set_psw_cc(vcpu, 3);
		return 0;
	}
}