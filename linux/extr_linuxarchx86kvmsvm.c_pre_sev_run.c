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
struct TYPE_5__ {int /*<<< orphan*/  kvm; } ;
struct vcpu_svm {int last_cpu; TYPE_3__* vmcb; TYPE_2__ vcpu; } ;
struct svm_cpu_data {TYPE_3__** sev_vmcbs; } ;
struct TYPE_4__ {int asid; int /*<<< orphan*/  tlb_ctl; } ;
struct TYPE_6__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_CONTROL_FLUSH_ASID ; 
 int /*<<< orphan*/  VMCB_ASID ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct svm_cpu_data* per_cpu (int /*<<< orphan*/ ,int) ; 
 int sev_get_asid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_data ; 

__attribute__((used)) static void pre_sev_run(struct vcpu_svm *svm, int cpu)
{
	struct svm_cpu_data *sd = per_cpu(svm_data, cpu);
	int asid = sev_get_asid(svm->vcpu.kvm);

	/* Assign the asid allocated with this SEV guest */
	svm->vmcb->control.asid = asid;

	/*
	 * Flush guest TLB:
	 *
	 * 1) when different VMCB for the same ASID is to be run on the same host CPU.
	 * 2) or this VMCB was executed on different host CPU in previous VMRUNs.
	 */
	if (sd->sev_vmcbs[asid] == svm->vmcb &&
	    svm->last_cpu == cpu)
		return;

	svm->last_cpu = cpu;
	sd->sev_vmcbs[asid] = svm->vmcb;
	svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ASID;
	mark_dirty(svm->vmcb, VMCB_ASID);
}