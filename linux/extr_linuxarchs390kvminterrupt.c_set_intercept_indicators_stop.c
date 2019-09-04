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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOP_INT ; 
 scalar_t__ kvm_s390_is_stop_irq_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_intercept_indicators_stop(struct kvm_vcpu *vcpu)
{
	if (kvm_s390_is_stop_irq_pending(vcpu))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOP_INT);
}