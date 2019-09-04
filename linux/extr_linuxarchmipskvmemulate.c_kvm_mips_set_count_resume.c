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
struct TYPE_2__ {int /*<<< orphan*/  count_resume; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 

int kvm_mips_set_count_resume(struct kvm_vcpu *vcpu, s64 count_resume)
{
	/*
	 * It doesn't make sense for the resume time to be in the future, as it
	 * would be possible for the next interrupt to be more than a full
	 * period in the future.
	 */
	if (count_resume < 0 || count_resume > ktime_to_ns(ktime_get()))
		return -EINVAL;

	vcpu->arch.count_resume = ns_to_ktime(count_resume);
	return 0;
}