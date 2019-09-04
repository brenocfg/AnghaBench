#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct machine_check_event {scalar_t__ version; scalar_t__ severity; scalar_t__ disposition; } ;
struct TYPE_5__ {unsigned long msr; unsigned long dsisr; } ;
struct TYPE_8__ {struct machine_check_event mce_evt; TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_3__* kvm; } ;
struct TYPE_6__ {scalar_t__ fwnmi_enabled; int /*<<< orphan*/  radix; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;

/* Variables and functions */
 unsigned long DSISR_MC_DERAT_MULTI ; 
 unsigned long DSISR_MC_SLB_MULTI ; 
 unsigned long DSISR_MC_SLB_PARITY ; 
 unsigned long DSISR_MC_SLB_PARMULTI ; 
 unsigned long DSISR_MC_TLB_MULTI ; 
 scalar_t__ MCE_DISPOSITION_RECOVERED ; 
 int /*<<< orphan*/  MCE_EVENT_DONTRELEASE ; 
 int /*<<< orphan*/  MCE_EVENT_RELEASE ; 
 scalar_t__ MCE_SEV_NO_ERROR ; 
 scalar_t__ MCE_V1 ; 
 unsigned long SRR1_MC_IFETCH_MASK ; 
 unsigned long SRR1_MC_IFETCH_SH ; 
#define  SRR1_MC_IFETCH_SLBMULTI 131 
#define  SRR1_MC_IFETCH_SLBPAR 130 
#define  SRR1_MC_IFETCH_SLBPARMULTI 129 
#define  SRR1_MC_IFETCH_TLBMULTI 128 
 unsigned long SRR1_MC_LDSTERR ; 
 scalar_t__ get_mce_event (struct machine_check_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_queue_event () ; 
 int /*<<< orphan*/  memset (struct machine_check_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reload_slb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  tlbiel_all_lpid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long kvmppc_realmode_mc_power7(struct kvm_vcpu *vcpu)
{
	unsigned long srr1 = vcpu->arch.shregs.msr;
	struct machine_check_event mce_evt;
	long handled = 1;

	if (srr1 & SRR1_MC_LDSTERR) {
		/* error on load/store */
		unsigned long dsisr = vcpu->arch.shregs.dsisr;

		if (dsisr & (DSISR_MC_SLB_PARMULTI | DSISR_MC_SLB_MULTI |
			     DSISR_MC_SLB_PARITY | DSISR_MC_DERAT_MULTI)) {
			/* flush and reload SLB; flushes D-ERAT too */
			reload_slb(vcpu);
			dsisr &= ~(DSISR_MC_SLB_PARMULTI | DSISR_MC_SLB_MULTI |
				   DSISR_MC_SLB_PARITY | DSISR_MC_DERAT_MULTI);
		}
		if (dsisr & DSISR_MC_TLB_MULTI) {
			tlbiel_all_lpid(vcpu->kvm->arch.radix);
			dsisr &= ~DSISR_MC_TLB_MULTI;
		}
		/* Any other errors we don't understand? */
		if (dsisr & 0xffffffffUL)
			handled = 0;
	}

	switch ((srr1 >> SRR1_MC_IFETCH_SH) & SRR1_MC_IFETCH_MASK) {
	case 0:
		break;
	case SRR1_MC_IFETCH_SLBPAR:
	case SRR1_MC_IFETCH_SLBMULTI:
	case SRR1_MC_IFETCH_SLBPARMULTI:
		reload_slb(vcpu);
		break;
	case SRR1_MC_IFETCH_TLBMULTI:
		tlbiel_all_lpid(vcpu->kvm->arch.radix);
		break;
	default:
		handled = 0;
	}

	/*
	 * See if we have already handled the condition in the linux host.
	 * We assume that if the condition is recovered then linux host
	 * will have generated an error log event that we will pick
	 * up and log later.
	 * Don't release mce event now. We will queue up the event so that
	 * we can log the MCE event info on host console.
	 */
	if (!get_mce_event(&mce_evt, MCE_EVENT_DONTRELEASE))
		goto out;

	if (mce_evt.version == MCE_V1 &&
	    (mce_evt.severity == MCE_SEV_NO_ERROR ||
	     mce_evt.disposition == MCE_DISPOSITION_RECOVERED))
		handled = 1;

out:
	/*
	 * For guest that supports FWNMI capability, hook the MCE event into
	 * vcpu structure. We are going to exit the guest with KVM_EXIT_NMI
	 * exit reason. On our way to exit we will pull this event from vcpu
	 * structure and print it from thread 0 of the core/subcore.
	 *
	 * For guest that does not support FWNMI capability (old QEMU):
	 * We are now going enter guest either through machine check
	 * interrupt (for unhandled errors) or will continue from
	 * current HSRR0 (for handled errors) in guest. Hence
	 * queue up the event so that we can log it from host console later.
	 */
	if (vcpu->kvm->arch.fwnmi_enabled) {
		/*
		 * Hook up the mce event on to vcpu structure.
		 * First clear the old event.
		 */
		memset(&vcpu->arch.mce_evt, 0, sizeof(vcpu->arch.mce_evt));
		if (get_mce_event(&mce_evt, MCE_EVENT_RELEASE)) {
			vcpu->arch.mce_evt = mce_evt;
		}
	} else
		machine_check_queue_event();

	return handled;
}