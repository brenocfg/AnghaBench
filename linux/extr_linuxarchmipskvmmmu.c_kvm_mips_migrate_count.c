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
struct TYPE_2__ {int /*<<< orphan*/  comparecount_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_restart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_mips_migrate_count(struct kvm_vcpu *vcpu)
{
	if (hrtimer_cancel(&vcpu->arch.comparecount_timer))
		hrtimer_restart(&vcpu->arch.comparecount_timer);
}