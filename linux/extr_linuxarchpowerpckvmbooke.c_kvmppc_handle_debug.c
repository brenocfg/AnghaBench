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
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  nip; } ;
struct debug_reg {int dbcr0; int /*<<< orphan*/  dac2; int /*<<< orphan*/  dac1; } ;
struct TYPE_8__ {int dbsr; TYPE_2__ regs; TYPE_1__* shared; struct debug_reg dbg_reg; } ;
struct kvm_vcpu {scalar_t__ guest_debug; TYPE_3__ arch; } ;
struct TYPE_9__ {int /*<<< orphan*/  address; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;
struct kvm_run {TYPE_5__ debug; } ;
struct TYPE_6__ {int msr; } ;

/* Variables and functions */
 int DBCR0_IDM ; 
 int DBSR_DAC1R ; 
 int DBSR_DAC1W ; 
 int DBSR_DAC2R ; 
 int DBSR_DAC2W ; 
 int DBSR_IAC1 ; 
 int DBSR_IAC2 ; 
 int DBSR_IAC3 ; 
 int DBSR_IAC4 ; 
 int DBSR_IDE ; 
 int DBSR_TIE ; 
 int /*<<< orphan*/  ESR_PTR ; 
 int /*<<< orphan*/  KVMPPC_DEBUG_BREAKPOINT ; 
 int /*<<< orphan*/  KVMPPC_DEBUG_WATCH_READ ; 
 int /*<<< orphan*/  KVMPPC_DEBUG_WATCH_WRITE ; 
 int MSR_DE ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  kvmppc_core_queue_debug (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_program (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_handle_debug(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	struct debug_reg *dbg_reg = &(vcpu->arch.dbg_reg);
	u32 dbsr = vcpu->arch.dbsr;

	if (vcpu->guest_debug == 0) {
		/*
		 * Debug resources belong to Guest.
		 * Imprecise debug event is not injected
		 */
		if (dbsr & DBSR_IDE) {
			dbsr &= ~DBSR_IDE;
			if (!dbsr)
				return RESUME_GUEST;
		}

		if (dbsr && (vcpu->arch.shared->msr & MSR_DE) &&
			    (vcpu->arch.dbg_reg.dbcr0 & DBCR0_IDM))
			kvmppc_core_queue_debug(vcpu);

		/* Inject a program interrupt if trap debug is not allowed */
		if ((dbsr & DBSR_TIE) && !(vcpu->arch.shared->msr & MSR_DE))
			kvmppc_core_queue_program(vcpu, ESR_PTR);

		return RESUME_GUEST;
	}

	/*
	 * Debug resource owned by userspace.
	 * Clear guest dbsr (vcpu->arch.dbsr)
	 */
	vcpu->arch.dbsr = 0;
	run->debug.arch.status = 0;
	run->debug.arch.address = vcpu->arch.regs.nip;

	if (dbsr & (DBSR_IAC1 | DBSR_IAC2 | DBSR_IAC3 | DBSR_IAC4)) {
		run->debug.arch.status |= KVMPPC_DEBUG_BREAKPOINT;
	} else {
		if (dbsr & (DBSR_DAC1W | DBSR_DAC2W))
			run->debug.arch.status |= KVMPPC_DEBUG_WATCH_WRITE;
		else if (dbsr & (DBSR_DAC1R | DBSR_DAC2R))
			run->debug.arch.status |= KVMPPC_DEBUG_WATCH_READ;
		if (dbsr & (DBSR_DAC1R | DBSR_DAC1W))
			run->debug.arch.address = dbg_reg->dac1;
		else if (dbsr & (DBSR_DAC2R | DBSR_DAC2W))
			run->debug.arch.address = dbg_reg->dac2;
	}

	return RESUME_HOST;
}