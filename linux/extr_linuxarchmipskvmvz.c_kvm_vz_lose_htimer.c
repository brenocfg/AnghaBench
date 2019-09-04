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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int MIPS_GCTL0_GT ; 
 int /*<<< orphan*/  _kvm_vz_restore_stimer (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  _kvm_vz_save_htimer (struct kvm_vcpu*,int*,int*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int read_c0_guestctl0 () ; 
 int /*<<< orphan*/  write_c0_guestctl0 (int) ; 

void kvm_vz_lose_htimer(struct kvm_vcpu *vcpu)
{
	u32 gctl0, compare, cause;

	preempt_disable();
	gctl0 = read_c0_guestctl0();
	if (gctl0 & MIPS_GCTL0_GT) {
		/* disable guest use of timer */
		write_c0_guestctl0(gctl0 & ~MIPS_GCTL0_GT);

		/* switch to soft timer */
		_kvm_vz_save_htimer(vcpu, &compare, &cause);

		/* leave soft timer in usable state */
		_kvm_vz_restore_stimer(vcpu, compare, cause);
	}
	preempt_enable();
}