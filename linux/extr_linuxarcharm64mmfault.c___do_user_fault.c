#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct siginfo {scalar_t__ si_addr; } ;
struct TYPE_5__ {unsigned long fault_address; unsigned int fault_code; } ;
struct TYPE_7__ {TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ESR_ELx_CM ; 
 int ESR_ELx_EC (unsigned int) ; 
#define  ESR_ELx_EC_DABT_LOW 129 
#define  ESR_ELx_EC_IABT_LOW 128 
 unsigned int ESR_ELx_EC_MASK ; 
 unsigned int ESR_ELx_FSC_FAULT ; 
 unsigned int ESR_ELx_IL ; 
 unsigned int ESR_ELx_WNR ; 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  arm64_force_sig_info (struct siginfo*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* current ; 
 TYPE_2__* esr_to_fault_info (unsigned int) ; 

__attribute__((used)) static void __do_user_fault(struct siginfo *info, unsigned int esr)
{
	current->thread.fault_address = (unsigned long)info->si_addr;

	/*
	 * If the faulting address is in the kernel, we must sanitize the ESR.
	 * From userspace's point of view, kernel-only mappings don't exist
	 * at all, so we report them as level 0 translation faults.
	 * (This is not quite the way that "no mapping there at all" behaves:
	 * an alignment fault not caused by the memory type would take
	 * precedence over translation fault for a real access to empty
	 * space. Unfortunately we can't easily distinguish "alignment fault
	 * not caused by memory type" from "alignment fault caused by memory
	 * type", so we ignore this wrinkle and just return the translation
	 * fault.)
	 */
	if (current->thread.fault_address >= TASK_SIZE) {
		switch (ESR_ELx_EC(esr)) {
		case ESR_ELx_EC_DABT_LOW:
			/*
			 * These bits provide only information about the
			 * faulting instruction, which userspace knows already.
			 * We explicitly clear bits which are architecturally
			 * RES0 in case they are given meanings in future.
			 * We always report the ESR as if the fault was taken
			 * to EL1 and so ISV and the bits in ISS[23:14] are
			 * clear. (In fact it always will be a fault to EL1.)
			 */
			esr &= ESR_ELx_EC_MASK | ESR_ELx_IL |
				ESR_ELx_CM | ESR_ELx_WNR;
			esr |= ESR_ELx_FSC_FAULT;
			break;
		case ESR_ELx_EC_IABT_LOW:
			/*
			 * Claim a level 0 translation fault.
			 * All other bits are architecturally RES0 for faults
			 * reported with that DFSC value, so we clear them.
			 */
			esr &= ESR_ELx_EC_MASK | ESR_ELx_IL;
			esr |= ESR_ELx_FSC_FAULT;
			break;
		default:
			/*
			 * This should never happen (entry.S only brings us
			 * into this code for insn and data aborts from a lower
			 * exception level). Fail safe by not providing an ESR
			 * context record at all.
			 */
			WARN(1, "ESR 0x%x is not DABT or IABT from EL0\n", esr);
			esr = 0;
			break;
		}
	}

	current->thread.fault_code = esr;
	arm64_force_sig_info(info, esr_to_fault_info(esr)->name, current);
}