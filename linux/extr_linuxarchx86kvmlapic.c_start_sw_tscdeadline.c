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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {unsigned long virtual_tsc_khz; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ tscdeadline; int /*<<< orphan*/  timer; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; struct kvm_vcpu* vcpu; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_PINNED ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_l1_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_timer_advance_ns ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rdtsc () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void start_sw_tscdeadline(struct kvm_lapic *apic)
{
	u64 guest_tsc, tscdeadline = apic->lapic_timer.tscdeadline;
	u64 ns = 0;
	ktime_t expire;
	struct kvm_vcpu *vcpu = apic->vcpu;
	unsigned long this_tsc_khz = vcpu->arch.virtual_tsc_khz;
	unsigned long flags;
	ktime_t now;

	if (unlikely(!tscdeadline || !this_tsc_khz))
		return;

	local_irq_save(flags);

	now = ktime_get();
	guest_tsc = kvm_read_l1_tsc(vcpu, rdtsc());
	if (likely(tscdeadline > guest_tsc)) {
		ns = (tscdeadline - guest_tsc) * 1000000ULL;
		do_div(ns, this_tsc_khz);
		expire = ktime_add_ns(now, ns);
		expire = ktime_sub_ns(expire, lapic_timer_advance_ns);
		hrtimer_start(&apic->lapic_timer.timer,
				expire, HRTIMER_MODE_ABS_PINNED);
	} else
		apic_timer_expired(apic);

	local_irq_restore(flags);
}