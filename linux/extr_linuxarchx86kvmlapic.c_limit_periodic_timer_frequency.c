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
struct TYPE_4__ {scalar_t__ period; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; TYPE_1__* vcpu; } ;
typedef  scalar_t__ s64 ;
struct TYPE_3__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 scalar_t__ apic_lvtt_period (struct kvm_lapic*) ; 
 long long min_timer_period_us ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void limit_periodic_timer_frequency(struct kvm_lapic *apic)
{
	/*
	 * Do not allow the guest to program periodic timers with small
	 * interval, since the hrtimers are not throttled by the host
	 * scheduler.
	 */
	if (apic_lvtt_period(apic) && apic->lapic_timer.period) {
		s64 min_period = min_timer_period_us * 1000LL;

		if (apic->lapic_timer.period < min_period) {
			pr_info_ratelimited(
			    "kvm: vcpu %i: requested %lld ns "
			    "lapic timer period limited to %lld ns\n",
			    apic->vcpu->vcpu_id,
			    apic->lapic_timer.period, min_period);
			apic->lapic_timer.period = min_period;
		}
	}
}