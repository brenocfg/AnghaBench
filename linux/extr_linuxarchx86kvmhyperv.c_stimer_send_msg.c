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
struct TYPE_2__ {int /*<<< orphan*/  payload; } ;
struct hv_message {TYPE_1__ u; } ;
struct kvm_vcpu_hv_stimer {int /*<<< orphan*/  config; int /*<<< orphan*/  exp_time; struct hv_message msg; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct hv_timer_message_payload {int /*<<< orphan*/  delivery_time; int /*<<< orphan*/  expiration_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_STIMER_SINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_time_ref_counter (int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int synic_deliver_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_message*) ; 
 int /*<<< orphan*/  vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static int stimer_send_msg(struct kvm_vcpu_hv_stimer *stimer)
{
	struct kvm_vcpu *vcpu = stimer_to_vcpu(stimer);
	struct hv_message *msg = &stimer->msg;
	struct hv_timer_message_payload *payload =
			(struct hv_timer_message_payload *)&msg->u.payload;

	payload->expiration_time = stimer->exp_time;
	payload->delivery_time = get_time_ref_counter(vcpu->kvm);
	return synic_deliver_msg(vcpu_to_synic(vcpu),
				 HV_STIMER_SINT(stimer->config), msg);
}