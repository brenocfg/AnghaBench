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
struct kvm_vcpu_hv_stimer {int msg_pending; int config; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int HV_STIMER_ENABLE ; 
 int HV_STIMER_PERIODIC ; 
 int stimer_send_msg (struct kvm_vcpu_hv_stimer*) ; 
 TYPE_1__* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_expiration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stimer_expiration(struct kvm_vcpu_hv_stimer *stimer)
{
	int r;

	stimer->msg_pending = true;
	r = stimer_send_msg(stimer);
	trace_kvm_hv_stimer_expiration(stimer_to_vcpu(stimer)->vcpu_id,
				       stimer->index, r);
	if (!r) {
		stimer->msg_pending = false;
		if (!(stimer->config & HV_STIMER_PERIODIC))
			stimer->config &= ~HV_STIMER_ENABLE;
	}
}