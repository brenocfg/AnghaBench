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
struct kvm_vcpu {TYPE_2__* kvm; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  start_stop_lock; } ;
struct TYPE_4__ {TYPE_1__ arch; struct kvm_vcpu** vcpus; int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOPPED ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  __disable_ibs_on_all_vcpus (TYPE_2__*) ; 
 int /*<<< orphan*/  __enable_ibs_on_vcpu (struct kvm_vcpu*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_vcpu_stopped (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_clear_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_s390_vcpu_start_stop (int /*<<< orphan*/ ,int) ; 

void kvm_s390_vcpu_start(struct kvm_vcpu *vcpu)
{
	int i, online_vcpus, started_vcpus = 0;

	if (!is_vcpu_stopped(vcpu))
		return;

	trace_kvm_s390_vcpu_start_stop(vcpu->vcpu_id, 1);
	/* Only one cpu at a time may enter/leave the STOPPED state. */
	spin_lock(&vcpu->kvm->arch.start_stop_lock);
	online_vcpus = atomic_read(&vcpu->kvm->online_vcpus);

	for (i = 0; i < online_vcpus; i++) {
		if (!is_vcpu_stopped(vcpu->kvm->vcpus[i]))
			started_vcpus++;
	}

	if (started_vcpus == 0) {
		/* we're the only active VCPU -> speed it up */
		__enable_ibs_on_vcpu(vcpu);
	} else if (started_vcpus == 1) {
		/*
		 * As we are starting a second VCPU, we have to disable
		 * the IBS facility on all VCPUs to remove potentially
		 * oustanding ENABLE requests.
		 */
		__disable_ibs_on_all_vcpus(vcpu->kvm);
	}

	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_STOPPED);
	/*
	 * Another VCPU might have used IBS while we were offline.
	 * Let's play safe and flush the VCPU at startup.
	 */
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	spin_unlock(&vcpu->kvm->arch.start_stop_lock);
	return;
}