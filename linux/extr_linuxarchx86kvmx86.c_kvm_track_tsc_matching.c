#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void kvm_track_tsc_matching(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	bool vcpus_matched;
	struct kvm_arch *ka = &vcpu->kvm->arch;
	struct pvclock_gtod_data *gtod = &pvclock_gtod_data;

	vcpus_matched = (ka->nr_vcpus_matched_tsc + 1 ==
			 atomic_read(&vcpu->kvm->online_vcpus));

	/*
	 * Once the masterclock is enabled, always perform request in
	 * order to update it.
	 *
	 * In order to enable masterclock, the host clocksource must be TSC
	 * and the vcpus need to have matched TSCs.  When that happens,
	 * perform request to enable masterclock.
	 */
	if (ka->use_master_clock ||
	    (gtod_is_based_on_tsc(gtod->clock.vclock_mode) && vcpus_matched))
		kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);

	trace_kvm_track_tsc(vcpu->vcpu_id, ka->nr_vcpus_matched_tsc,
			    atomic_read(&vcpu->kvm->online_vcpus),
		            ka->use_master_clock, gtod->clock.vclock_mode);
#endif
}