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
typedef  scalar_t__ u32 ;
struct mips_coproc {int dummy; } ;
struct TYPE_3__ {int count_period; int /*<<< orphan*/  comparecount_timer; scalar_t__ count_bias; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* queue_timer_int ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_get_expires (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* kvm_mips_callbacks ; 
 scalar_t__ kvm_mips_ktime_to_count (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_c0_guest_compare (struct mips_coproc*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static u32 kvm_mips_read_count_running(struct kvm_vcpu *vcpu, ktime_t now)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	ktime_t expires, threshold;
	u32 count, compare;
	int running;

	/* Calculate the biased and scaled guest CP0_Count */
	count = vcpu->arch.count_bias + kvm_mips_ktime_to_count(vcpu, now);
	compare = kvm_read_c0_guest_compare(cop0);

	/*
	 * Find whether CP0_Count has reached the closest timer interrupt. If
	 * not, we shouldn't inject it.
	 */
	if ((s32)(count - compare) < 0)
		return count;

	/*
	 * The CP0_Count we're going to return has already reached the closest
	 * timer interrupt. Quickly check if it really is a new interrupt by
	 * looking at whether the interval until the hrtimer expiry time is
	 * less than 1/4 of the timer period.
	 */
	expires = hrtimer_get_expires(&vcpu->arch.comparecount_timer);
	threshold = ktime_add_ns(now, vcpu->arch.count_period / 4);
	if (ktime_before(expires, threshold)) {
		/*
		 * Cancel it while we handle it so there's no chance of
		 * interference with the timeout handler.
		 */
		running = hrtimer_cancel(&vcpu->arch.comparecount_timer);

		/* Nothing should be waiting on the timeout */
		kvm_mips_callbacks->queue_timer_int(vcpu);

		/*
		 * Restart the timer if it was running based on the expiry time
		 * we read, so that we don't push it back 2 periods.
		 */
		if (running) {
			expires = ktime_add_ns(expires,
					       vcpu->arch.count_period);
			hrtimer_start(&vcpu->arch.comparecount_timer, expires,
				      HRTIMER_MODE_ABS);
		}
	}

	return count;
}