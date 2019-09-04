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
 int /*<<< orphan*/  MSR_F16H_DR0_ADDR_MASK ; 
 int /*<<< orphan*/  MSR_F16H_DR1_ADDR_MASK ; 
 int /*<<< orphan*/  X86_FEATURE_BPEXT ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void set_dr_addr_mask(unsigned long mask, int dr)
{
	if (!boot_cpu_has(X86_FEATURE_BPEXT))
		return;

	switch (dr) {
	case 0:
		wrmsr(MSR_F16H_DR0_ADDR_MASK, mask, 0);
		break;
	case 1:
	case 2:
	case 3:
		wrmsr(MSR_F16H_DR1_ADDR_MASK - 1 + dr, mask, 0);
		break;
	default:
		break;
	}
}