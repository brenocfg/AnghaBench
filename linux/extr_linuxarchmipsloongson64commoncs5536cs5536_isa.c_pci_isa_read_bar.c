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
 int PCI_BASE_ADDRESS_SPACE_IO ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 
 int* bar_space_range ; 
 int /*<<< orphan*/ * divil_msr_reg ; 
 int* soft_bar_flag ; 

u32 pci_isa_read_bar(int n)
{
	u32 conf_data = 0;
	u32 hi, lo;

	_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
	if (lo & soft_bar_flag[n]) {
		conf_data = bar_space_range[n] | PCI_BASE_ADDRESS_SPACE_IO;
		lo &= ~soft_bar_flag[n];
		_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
	} else {
		_rdmsr(divil_msr_reg[n], &hi, &lo);
		conf_data = lo & bar_space_range[n];
		conf_data |= 0x01;
		conf_data &= ~0x02;
	}
	return conf_data;
}