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
struct kvm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void pvclock_update_vm_gtod_copy(struct kvm *kvm)
{
#ifdef CONFIG_X86_64
	struct kvm_arch *ka = &kvm->arch;
	int vclock_mode;
	bool host_tsc_clocksource, vcpus_matched;

	vcpus_matched = (ka->nr_vcpus_matched_tsc + 1 ==
			atomic_read(&kvm->online_vcpus));

	/*
	 * If the host uses TSC clock, then passthrough TSC as stable
	 * to the guest.
	 */
	host_tsc_clocksource = kvm_get_time_and_clockread(
					&ka->master_kernel_ns,
					&ka->master_cycle_now);

	ka->use_master_clock = host_tsc_clocksource && vcpus_matched
				&& !ka->backwards_tsc_observed
				&& !ka->boot_vcpu_runs_old_kvmclock;

	if (ka->use_master_clock)
		atomic_set(&kvm_guest_has_master_clock, 1);

	vclock_mode = pvclock_gtod_data.clock.vclock_mode;
	trace_kvm_update_master_clock(ka->use_master_clock, vclock_mode,
					vcpus_matched);
#endif
}