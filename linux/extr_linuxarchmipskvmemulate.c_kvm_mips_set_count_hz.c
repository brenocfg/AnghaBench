#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {scalar_t__ count_hz; scalar_t__ count_bias; scalar_t__ count_dyn_bias; int /*<<< orphan*/  count_period; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  div_u64 (int,scalar_t__) ; 
 int kvm_mips_count_disabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_count_time (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_freeze_hrtimer (struct kvm_vcpu*,scalar_t__*) ; 
 scalar_t__ kvm_mips_ktime_to_count (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mips_resume_hrtimer (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kvm_read_c0_guest_count (struct mips_coproc*) ; 

int kvm_mips_set_count_hz(struct kvm_vcpu *vcpu, s64 count_hz)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	int dc;
	ktime_t now;
	u32 count;

	/* ensure the frequency is in a sensible range... */
	if (count_hz <= 0 || count_hz > NSEC_PER_SEC)
		return -EINVAL;
	/* ... and has actually changed */
	if (vcpu->arch.count_hz == count_hz)
		return 0;

	/* Safely freeze timer so we can keep it continuous */
	dc = kvm_mips_count_disabled(vcpu);
	if (dc) {
		now = kvm_mips_count_time(vcpu);
		count = kvm_read_c0_guest_count(cop0);
	} else {
		now = kvm_mips_freeze_hrtimer(vcpu, &count);
	}

	/* Update the frequency */
	vcpu->arch.count_hz = count_hz;
	vcpu->arch.count_period = div_u64((u64)NSEC_PER_SEC << 32, count_hz);
	vcpu->arch.count_dyn_bias = 0;

	/* Calculate adjusted bias so dynamic count is unchanged */
	vcpu->arch.count_bias = count - kvm_mips_ktime_to_count(vcpu, now);

	/* Update and resume hrtimer */
	if (!dc)
		kvm_mips_resume_hrtimer(vcpu, now, count);
	return 0;
}