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
struct kvm_vcpu_hv_stimer {int config; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int HV_STIMER_ENABLE ; 
 scalar_t__ HV_STIMER_SINT (int) ; 
 int /*<<< orphan*/  stimer_cleanup (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  stimer_mark_pending (struct kvm_vcpu_hv_stimer*,int) ; 
 TYPE_1__* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stimer_set_config(struct kvm_vcpu_hv_stimer *stimer, u64 config,
			     bool host)
{
	trace_kvm_hv_stimer_set_config(stimer_to_vcpu(stimer)->vcpu_id,
				       stimer->index, config, host);

	stimer_cleanup(stimer);
	if ((stimer->config & HV_STIMER_ENABLE) && HV_STIMER_SINT(config) == 0)
		config &= ~HV_STIMER_ENABLE;
	stimer->config = config;
	stimer_mark_pending(stimer, false);
	return 0;
}