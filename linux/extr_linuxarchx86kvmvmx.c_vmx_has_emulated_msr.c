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

/* Variables and functions */
#define  MSR_AMD64_VIRT_SPEC_CTRL 129 
#define  MSR_IA32_SMBASE 128 
 int /*<<< orphan*/  emulate_invalid_guest_state ; 
 int /*<<< orphan*/  enable_unrestricted_guest ; 

__attribute__((used)) static bool vmx_has_emulated_msr(int index)
{
	switch (index) {
	case MSR_IA32_SMBASE:
		/*
		 * We cannot do SMM unless we can run the guest in big
		 * real mode.
		 */
		return enable_unrestricted_guest || emulate_invalid_guest_state;
	case MSR_AMD64_VIRT_SPEC_CTRL:
		/* This is AMD only.  */
		return false;
	default:
		return true;
	}
}