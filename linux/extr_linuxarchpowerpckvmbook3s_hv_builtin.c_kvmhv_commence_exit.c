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
struct kvmppc_vcore {int entry_exit_map; int pcpu; } ;
struct kvm_split_mode {int do_restore; scalar_t__* napped; scalar_t__ lpcr_req; struct kvmppc_vcore** vc; } ;
struct TYPE_3__ {int ptid; int tid; struct kvmppc_vcore* kvm_vcore; struct kvm_split_mode* kvm_split_mode; } ;
struct TYPE_4__ {TYPE_1__ kvm_hstate; } ;

/* Variables and functions */
 int BOOK3S_INTERRUPT_HV_DECREMENTER ; 
 int MAX_SUBCORES ; 
 int VCORE_EXIT_REQ ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  kvmhv_interrupt_vcore (struct kvmppc_vcore*,int) ; 
 int /*<<< orphan*/  kvmhv_rm_send_ipi (int) ; 
 TYPE_2__* local_paca ; 
 int threads_per_core ; 

void kvmhv_commence_exit(int trap)
{
	struct kvmppc_vcore *vc = local_paca->kvm_hstate.kvm_vcore;
	int ptid = local_paca->kvm_hstate.ptid;
	struct kvm_split_mode *sip = local_paca->kvm_hstate.kvm_split_mode;
	int me, ee, i, t;
	int cpu0;

	/* Set our bit in the threads-exiting-guest map in the 0xff00
	   bits of vcore->entry_exit_map */
	me = 0x100 << ptid;
	do {
		ee = vc->entry_exit_map;
	} while (cmpxchg(&vc->entry_exit_map, ee, ee | me) != ee);

	/* Are we the first here? */
	if ((ee >> 8) != 0)
		return;

	/*
	 * Trigger the other threads in this vcore to exit the guest.
	 * If this is a hypervisor decrementer interrupt then they
	 * will be already on their way out of the guest.
	 */
	if (trap != BOOK3S_INTERRUPT_HV_DECREMENTER)
		kvmhv_interrupt_vcore(vc, ee & ~(1 << ptid));

	/*
	 * If we are doing dynamic micro-threading, interrupt the other
	 * subcores to pull them out of their guests too.
	 */
	if (!sip)
		return;

	for (i = 0; i < MAX_SUBCORES; ++i) {
		vc = sip->vc[i];
		if (!vc)
			break;
		do {
			ee = vc->entry_exit_map;
			/* Already asked to exit? */
			if ((ee >> 8) != 0)
				break;
		} while (cmpxchg(&vc->entry_exit_map, ee,
				 ee | VCORE_EXIT_REQ) != ee);
		if ((ee >> 8) == 0)
			kvmhv_interrupt_vcore(vc, ee);
	}

	/*
	 * On POWER9 when running a HPT guest on a radix host (sip != NULL),
	 * we have to interrupt inactive CPU threads to get them to
	 * restore the host LPCR value.
	 */
	if (sip->lpcr_req) {
		if (cmpxchg(&sip->do_restore, 0, 1) == 0) {
			vc = local_paca->kvm_hstate.kvm_vcore;
			cpu0 = vc->pcpu + ptid - local_paca->kvm_hstate.tid;
			for (t = 1; t < threads_per_core; ++t) {
				if (sip->napped[t])
					kvmhv_rm_send_ipi(cpu0 + t);
			}
		}
	}
}