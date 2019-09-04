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

/* Variables and functions */
 int /*<<< orphan*/  GLCP_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_SOFT_COM ; 
 int PCI_BAR_RANGE_MASK ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 
 int* bar_space_len ; 
 int* bar_space_range ; 
 int /*<<< orphan*/ * divil_msr_reg ; 
 int /*<<< orphan*/ * sb_msr_reg ; 
 int* soft_bar_flag ; 

void pci_isa_write_bar(int n, u32 value)
{
	u32 hi = 0, lo = value;

	if (value == PCI_BAR_RANGE_MASK) {
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		lo |= soft_bar_flag[n];
		_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
	} else if (value & 0x01) {
		/* NATIVE reg */
		hi = 0x0000f001;
		lo &= bar_space_range[n];
		_wrmsr(divil_msr_reg[n], hi, lo);

		/* RCONFx is 4bytes in units for I/O space */
		hi = ((value & 0x000ffffc) << 12) |
		    ((bar_space_len[n] - 4) << 12) | 0x01;
		lo = ((value & 0x000ffffc) << 12) | 0x01;
		_wrmsr(sb_msr_reg[n], hi, lo);
	}
}