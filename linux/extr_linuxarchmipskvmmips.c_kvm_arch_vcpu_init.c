#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  function; } ;
struct TYPE_4__ {TYPE_3__ comparecount_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_5__ {int (* vcpu_init ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_mips_comparecount_wakeup ; 
 int stub1 (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
{
	int err;

	err = kvm_mips_callbacks->vcpu_init(vcpu);
	if (err)
		return err;

	hrtimer_init(&vcpu->arch.comparecount_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	vcpu->arch.comparecount_timer.function = kvm_mips_comparecount_wakeup;
	return 0;
}