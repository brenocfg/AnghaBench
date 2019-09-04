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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTRR_TYPE_UNCACHABLE ; 
 int /*<<< orphan*/  MTRR_TYPE_WRBACK ; 
 int /*<<< orphan*/  X86_FEATURE_MTRR ; 
 scalar_t__ guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 mtrr_disabled_type(struct kvm_vcpu *vcpu)
{
	/*
	 * Intel SDM 11.11.2.2: all MTRRs are disabled when
	 * IA32_MTRR_DEF_TYPE.E bit is cleared, and the UC
	 * memory type is applied to all of physical memory.
	 *
	 * However, virtual machines can be run with CPUID such that
	 * there are no MTRRs.  In that case, the firmware will never
	 * enable MTRRs and it is obviously undesirable to run the
	 * guest entirely with UC memory and we use WB.
	 */
	if (guest_cpuid_has(vcpu, X86_FEATURE_MTRR))
		return MTRR_TYPE_UNCACHABLE;
	else
		return MTRR_TYPE_WRBACK;
}