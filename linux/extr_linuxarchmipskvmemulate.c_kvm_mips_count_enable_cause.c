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
typedef  int /*<<< orphan*/  u32 ;
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAUSEF_DC ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_cause (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mips_write_count (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_count (struct mips_coproc*) ; 

void kvm_mips_count_enable_cause(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	u32 count;

	kvm_clear_c0_guest_cause(cop0, CAUSEF_DC);

	/*
	 * Set the dynamic count to match the static count.
	 * This starts the hrtimer if count_ctl.DC allows it.
	 * Otherwise it conveniently updates the biases.
	 */
	count = kvm_read_c0_guest_count(cop0);
	kvm_mips_write_count(vcpu, count);
}