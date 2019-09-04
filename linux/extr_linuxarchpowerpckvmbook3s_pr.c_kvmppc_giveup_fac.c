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
typedef  int /*<<< orphan*/  ulong ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

void kvmppc_giveup_fac(struct kvm_vcpu *vcpu, ulong fac)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (!(vcpu->arch.shadow_fscr & (1ULL << fac))) {
		/* Facility not available to the guest, ignore giveup request*/
		return;
	}

	switch (fac) {
	case FSCR_TAR_LG:
		vcpu->arch.tar = mfspr(SPRN_TAR);
		mtspr(SPRN_TAR, current->thread.tar);
		vcpu->arch.shadow_fscr &= ~FSCR_TAR;
		break;
	}
#endif
}