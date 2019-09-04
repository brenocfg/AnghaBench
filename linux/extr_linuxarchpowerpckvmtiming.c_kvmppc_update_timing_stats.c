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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__ tv64; } ;
struct TYPE_5__ {scalar_t__ tv64; } ;
struct TYPE_6__ {scalar_t__ timing_last_exit; int last_exit_type; TYPE_1__ timing_exit; TYPE_2__ timing_last_enter; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int TIMEINGUEST ; 
 int /*<<< orphan*/  add_exit_timing (struct kvm_vcpu*,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

void kvmppc_update_timing_stats(struct kvm_vcpu *vcpu)
{
	u64 exit = vcpu->arch.timing_last_exit;
	u64 enter = vcpu->arch.timing_last_enter.tv64;

	/* save exit time, used next exit when the reenter time is known */
	vcpu->arch.timing_last_exit = vcpu->arch.timing_exit.tv64;

	if (unlikely(vcpu->arch.last_exit_type == 0xDEAD || exit == 0))
		return; /* skip incomplete cycle (e.g. after reset) */

	/* update statistics for average and standard deviation */
	add_exit_timing(vcpu, (enter - exit), vcpu->arch.last_exit_type);
	/* enter -> timing_last_exit is time spent in guest - log this too */
	add_exit_timing(vcpu, (vcpu->arch.timing_last_exit - enter),
			TIMEINGUEST);
}