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
struct TYPE_3__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* dequeue_timer_int ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ CAUSEF_TI ; 
 int /*<<< orphan*/  CONFIG_KVM_MIPS_VZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* kvm_mips_callbacks ; 
 int kvm_mips_count_disabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_freeze_hrtimer (struct kvm_vcpu*,scalar_t__*) ; 
 int /*<<< orphan*/  kvm_mips_resume_hrtimer (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kvm_read_c0_guest_cause (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_compare (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_cause (struct mips_coproc*,scalar_t__) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_compare (struct mips_coproc*,scalar_t__) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ read_c0_count () ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  write_c0_gtoffset (scalar_t__) ; 

void kvm_mips_write_compare(struct kvm_vcpu *vcpu, u32 compare, bool ack)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	int dc;
	u32 old_compare = kvm_read_c0_guest_compare(cop0);
	s32 delta = compare - old_compare;
	u32 cause;
	ktime_t now = ktime_set(0, 0); /* silence bogus GCC warning */
	u32 count;

	/* if unchanged, must just be an ack */
	if (old_compare == compare) {
		if (!ack)
			return;
		kvm_mips_callbacks->dequeue_timer_int(vcpu);
		kvm_write_c0_guest_compare(cop0, compare);
		return;
	}

	/*
	 * If guest CP0_Compare moves forward, CP0_GTOffset should be adjusted
	 * too to prevent guest CP0_Count hitting guest CP0_Compare.
	 *
	 * The new GTOffset corresponds to the new value of CP0_Compare, and is
	 * set prior to it being written into the guest context. We disable
	 * preemption until the new value is written to prevent restore of a
	 * GTOffset corresponding to the old CP0_Compare value.
	 */
	if (IS_ENABLED(CONFIG_KVM_MIPS_VZ) && delta > 0) {
		preempt_disable();
		write_c0_gtoffset(compare - read_c0_count());
		back_to_back_c0_hazard();
	}

	/* freeze_hrtimer() takes care of timer interrupts <= count */
	dc = kvm_mips_count_disabled(vcpu);
	if (!dc)
		now = kvm_mips_freeze_hrtimer(vcpu, &count);

	if (ack)
		kvm_mips_callbacks->dequeue_timer_int(vcpu);
	else if (IS_ENABLED(CONFIG_KVM_MIPS_VZ))
		/*
		 * With VZ, writing CP0_Compare acks (clears) CP0_Cause.TI, so
		 * preserve guest CP0_Cause.TI if we don't want to ack it.
		 */
		cause = kvm_read_c0_guest_cause(cop0);

	kvm_write_c0_guest_compare(cop0, compare);

	if (IS_ENABLED(CONFIG_KVM_MIPS_VZ)) {
		if (delta > 0)
			preempt_enable();

		back_to_back_c0_hazard();

		if (!ack && cause & CAUSEF_TI)
			kvm_write_c0_guest_cause(cop0, cause);
	}

	/* resume_hrtimer() takes care of timer interrupts > count */
	if (!dc)
		kvm_mips_resume_hrtimer(vcpu, now, count);

	/*
	 * If guest CP0_Compare is moving backward, we delay CP0_GTOffset change
	 * until after the new CP0_Compare is written, otherwise new guest
	 * CP0_Count could hit new guest CP0_Compare.
	 */
	if (IS_ENABLED(CONFIG_KVM_MIPS_VZ) && delta <= 0)
		write_c0_gtoffset(compare - read_c0_count());
}