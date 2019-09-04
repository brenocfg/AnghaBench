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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MIPS_GCTL0_GT ; 
 int /*<<< orphan*/  _kvm_vz_save_htimer (struct kvm_vcpu*,int*,int*) ; 
 int /*<<< orphan*/  kvm_write_sw_gc0_cause (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_write_sw_gc0_compare (struct mips_coproc*,int) ; 
 int read_c0_guestctl0 () ; 
 int read_gc0_cause () ; 
 int read_gc0_compare () ; 
 int /*<<< orphan*/  write_c0_guestctl0 (int) ; 

__attribute__((used)) static void kvm_vz_save_timer(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	u32 gctl0, compare, cause;

	gctl0 = read_c0_guestctl0();
	if (gctl0 & MIPS_GCTL0_GT) {
		/* disable guest use of hard timer */
		write_c0_guestctl0(gctl0 & ~MIPS_GCTL0_GT);

		/* save hard timer state */
		_kvm_vz_save_htimer(vcpu, &compare, &cause);
	} else {
		compare = read_gc0_compare();
		cause = read_gc0_cause();
	}

	/* save timer-related state to VCPU context */
	kvm_write_sw_gc0_cause(cop0, cause);
	kvm_write_sw_gc0_compare(cop0, compare);
}