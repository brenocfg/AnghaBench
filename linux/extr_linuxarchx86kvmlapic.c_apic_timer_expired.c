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
struct swait_queue_head {int dummy; } ;
struct kvm_vcpu {struct swait_queue_head wq; } ;
struct kvm_timer {int /*<<< orphan*/  tscdeadline; int /*<<< orphan*/  expired_tscdeadline; int /*<<< orphan*/  pending; } ;
struct kvm_lapic {struct kvm_timer lapic_timer; struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 scalar_t__ apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_set_pending_timer (struct kvm_vcpu*) ; 
 scalar_t__ swait_active (struct swait_queue_head*) ; 
 int /*<<< orphan*/  swake_up_one (struct swait_queue_head*) ; 

__attribute__((used)) static void apic_timer_expired(struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu = apic->vcpu;
	struct swait_queue_head *q = &vcpu->wq;
	struct kvm_timer *ktimer = &apic->lapic_timer;

	if (atomic_read(&apic->lapic_timer.pending))
		return;

	atomic_inc(&apic->lapic_timer.pending);
	kvm_set_pending_timer(vcpu);

	/*
	 * For x86, the atomic_inc() is serialized, thus
	 * using swait_active() is safe.
	 */
	if (swait_active(q))
		swake_up_one(q);

	if (apic_lvtt_tscdeadline(apic))
		ktimer->expired_tscdeadline = ktimer->tscdeadline;
}