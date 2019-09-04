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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tsr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int TSR_ENW ; 
 int TSR_WIS ; 
 int /*<<< orphan*/  arm_next_watchdog (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  clear_bits (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_timer_ints (struct kvm_vcpu*) ; 

void kvmppc_clr_tsr_bits(struct kvm_vcpu *vcpu, u32 tsr_bits)
{
	clear_bits(tsr_bits, &vcpu->arch.tsr);

	/*
	 * We may have stopped the watchdog due to
	 * being stuck on final expiration.
	 */
	if (tsr_bits & (TSR_ENW | TSR_WIS))
		arm_next_watchdog(vcpu);

	update_timer_ints(vcpu);
}