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
typedef  unsigned int u64 ;
struct TYPE_10__ {TYPE_4__* sie_block; } ;
struct kvm_vcpu {TYPE_5__ arch; TYPE_3__* run; } ;
typedef  unsigned int freg_t ;
typedef  int /*<<< orphan*/  __vector128 ;
struct TYPE_9__ {unsigned int gpsw; unsigned int todpr; int ckc; unsigned int gcr; } ;
struct TYPE_6__ {unsigned int* fprs; unsigned int* gprs; unsigned int fpc; unsigned int acrs; scalar_t__ vrs; } ;
struct TYPE_7__ {TYPE_1__ regs; } ;
struct TYPE_8__ {TYPE_2__ s; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long KVM_S390_STORE_STATUS_NOADDR ; 
 unsigned long KVM_S390_STORE_STATUS_PREFIXED ; 
 scalar_t__ MACHINE_HAS_VX ; 
 int NUM_FPRS ; 
 unsigned long __LC_AREGS_SAVE_AREA ; 
 unsigned long __LC_CLOCK_COMP_SAVE_AREA ; 
 unsigned long __LC_CPU_TIMER_SAVE_AREA ; 
 unsigned long __LC_CREGS_SAVE_AREA ; 
 unsigned long __LC_FPREGS_SAVE_AREA ; 
 unsigned long __LC_FP_CREG_SAVE_AREA ; 
 unsigned long __LC_GPREGS_SAVE_AREA ; 
 unsigned long __LC_PREFIX_SAVE_AREA ; 
 unsigned long __LC_PSW_SAVE_AREA ; 
 unsigned long __LC_TOD_PROGREG_SAVE_AREA ; 
 int /*<<< orphan*/  convert_vx_to_fp (unsigned int*,int /*<<< orphan*/ *) ; 
 unsigned int kvm_s390_get_cpu_timer (struct kvm_vcpu*) ; 
 unsigned int kvm_s390_get_prefix (struct kvm_vcpu*) ; 
 int write_guest_abs (struct kvm_vcpu*,unsigned long,...) ; 
 scalar_t__ write_guest_real (struct kvm_vcpu*,int,unsigned char*,int) ; 

int kvm_s390_store_status_unloaded(struct kvm_vcpu *vcpu, unsigned long gpa)
{
	unsigned char archmode = 1;
	freg_t fprs[NUM_FPRS];
	unsigned int px;
	u64 clkcomp, cputm;
	int rc;

	px = kvm_s390_get_prefix(vcpu);
	if (gpa == KVM_S390_STORE_STATUS_NOADDR) {
		if (write_guest_abs(vcpu, 163, &archmode, 1))
			return -EFAULT;
		gpa = 0;
	} else if (gpa == KVM_S390_STORE_STATUS_PREFIXED) {
		if (write_guest_real(vcpu, 163, &archmode, 1))
			return -EFAULT;
		gpa = px;
	} else
		gpa -= __LC_FPREGS_SAVE_AREA;

	/* manually convert vector registers if necessary */
	if (MACHINE_HAS_VX) {
		convert_vx_to_fp(fprs, (__vector128 *) vcpu->run->s.regs.vrs);
		rc = write_guest_abs(vcpu, gpa + __LC_FPREGS_SAVE_AREA,
				     fprs, 128);
	} else {
		rc = write_guest_abs(vcpu, gpa + __LC_FPREGS_SAVE_AREA,
				     vcpu->run->s.regs.fprs, 128);
	}
	rc |= write_guest_abs(vcpu, gpa + __LC_GPREGS_SAVE_AREA,
			      vcpu->run->s.regs.gprs, 128);
	rc |= write_guest_abs(vcpu, gpa + __LC_PSW_SAVE_AREA,
			      &vcpu->arch.sie_block->gpsw, 16);
	rc |= write_guest_abs(vcpu, gpa + __LC_PREFIX_SAVE_AREA,
			      &px, 4);
	rc |= write_guest_abs(vcpu, gpa + __LC_FP_CREG_SAVE_AREA,
			      &vcpu->run->s.regs.fpc, 4);
	rc |= write_guest_abs(vcpu, gpa + __LC_TOD_PROGREG_SAVE_AREA,
			      &vcpu->arch.sie_block->todpr, 4);
	cputm = kvm_s390_get_cpu_timer(vcpu);
	rc |= write_guest_abs(vcpu, gpa + __LC_CPU_TIMER_SAVE_AREA,
			      &cputm, 8);
	clkcomp = vcpu->arch.sie_block->ckc >> 8;
	rc |= write_guest_abs(vcpu, gpa + __LC_CLOCK_COMP_SAVE_AREA,
			      &clkcomp, 8);
	rc |= write_guest_abs(vcpu, gpa + __LC_AREGS_SAVE_AREA,
			      &vcpu->run->s.regs.acrs, 64);
	rc |= write_guest_abs(vcpu, gpa + __LC_CREGS_SAVE_AREA,
			      &vcpu->arch.sie_block->gcr, 128);
	return rc ? -EFAULT : 0;
}