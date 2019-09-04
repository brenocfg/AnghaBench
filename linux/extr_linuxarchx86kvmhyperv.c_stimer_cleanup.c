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
struct kvm_vcpu_hv_stimer {int msg_pending; scalar_t__ exp_time; int /*<<< orphan*/  index; int /*<<< orphan*/  timer; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  stimer_pending_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 struct kvm_vcpu* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

__attribute__((used)) static void stimer_cleanup(struct kvm_vcpu_hv_stimer *stimer)
{
	struct kvm_vcpu *vcpu = stimer_to_vcpu(stimer);

	trace_kvm_hv_stimer_cleanup(stimer_to_vcpu(stimer)->vcpu_id,
				    stimer->index);

	hrtimer_cancel(&stimer->timer);
	clear_bit(stimer->index,
		  vcpu_to_hv_vcpu(vcpu)->stimer_pending_bitmap);
	stimer->msg_pending = false;
	stimer->exp_time = 0;
}