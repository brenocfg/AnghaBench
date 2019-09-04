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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct hrtimer {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct hrtimer timer; } ;
struct kvm_pit {TYPE_3__ pit_state; } ;
struct TYPE_4__ {struct kvm_pit* vpit; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 scalar_t__ hrtimer_cancel (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_start_expires (struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void __kvm_migrate_pit_timer(struct kvm_vcpu *vcpu)
{
	struct kvm_pit *pit = vcpu->kvm->arch.vpit;
	struct hrtimer *timer;

	if (!kvm_vcpu_is_bsp(vcpu) || !pit)
		return;

	timer = &pit->pit_state.timer;
	mutex_lock(&pit->pit_state.lock);
	if (hrtimer_cancel(timer))
		hrtimer_start_expires(timer, HRTIMER_MODE_ABS);
	mutex_unlock(&pit->pit_state.lock);
}