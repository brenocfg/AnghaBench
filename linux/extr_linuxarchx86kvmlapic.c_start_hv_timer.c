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
struct kvm_timer {int hv_timer_in_use; int /*<<< orphan*/  pending; int /*<<< orphan*/  timer; int /*<<< orphan*/  tscdeadline; } ;
struct kvm_lapic {TYPE_1__* vcpu; struct kvm_timer lapic_timer; } ;
struct TYPE_4__ {int (* set_hv_timer ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_lvtt_period (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  preemptible () ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_hv_timer_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool start_hv_timer(struct kvm_lapic *apic)
{
	struct kvm_timer *ktimer = &apic->lapic_timer;
	int r;

	WARN_ON(preemptible());
	if (!kvm_x86_ops->set_hv_timer)
		return false;

	if (!apic_lvtt_period(apic) && atomic_read(&ktimer->pending))
		return false;

	if (!ktimer->tscdeadline)
		return false;

	r = kvm_x86_ops->set_hv_timer(apic->vcpu, ktimer->tscdeadline);
	if (r < 0)
		return false;

	ktimer->hv_timer_in_use = true;
	hrtimer_cancel(&ktimer->timer);

	/*
	 * Also recheck ktimer->pending, in case the sw timer triggered in
	 * the window.  For periodic timer, leave the hv timer running for
	 * simplicity, and the deadline will be recomputed on the next vmexit.
	 */
	if (!apic_lvtt_period(apic) && (r || atomic_read(&ktimer->pending))) {
		if (r)
			apic_timer_expired(apic);
		return false;
	}

	trace_kvm_hv_timer_state(apic->vcpu->vcpu_id, true);
	return true;
}