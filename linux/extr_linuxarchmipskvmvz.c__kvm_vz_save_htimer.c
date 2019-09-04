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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_EXC_INT_TIMER ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  kvm_mips_restore_hrtimer (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kvm_vz_queue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int read_gc0_cause () ; 
 int read_gc0_compare () ; 
 int read_gc0_count () ; 

__attribute__((used)) static void _kvm_vz_save_htimer(struct kvm_vcpu *vcpu,
				u32 *out_compare, u32 *out_cause)
{
	u32 cause, compare, before_count, end_count;
	ktime_t before_time;

	compare = read_gc0_compare();
	*out_compare = compare;

	before_time = ktime_get();

	/*
	 * Record the CP0_Count *prior* to saving CP0_Cause, so we have a time
	 * at which no pending timer interrupt is missing.
	 */
	before_count = read_gc0_count();
	back_to_back_c0_hazard();
	cause = read_gc0_cause();
	*out_cause = cause;

	/*
	 * Record a final CP0_Count which we will transfer to the soft-timer.
	 * This is recorded *after* saving CP0_Cause, so we don't get any timer
	 * interrupts from just after the final CP0_Count point.
	 */
	back_to_back_c0_hazard();
	end_count = read_gc0_count();

	/*
	 * The above sequence isn't atomic, so we could miss a timer interrupt
	 * between reading CP0_Cause and end_count. Detect and record any timer
	 * interrupt due between before_count and end_count.
	 */
	if (end_count - before_count > compare - before_count - 1)
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_TIMER);

	/*
	 * Restore soft-timer, ignoring a small amount of negative drift due to
	 * delay between freeze_hrtimer and setting CP0_GTOffset.
	 */
	kvm_mips_restore_hrtimer(vcpu, before_time, end_count, -0x10000);
}