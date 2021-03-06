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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_BAR_REG_ADDRESS ; 
 int ath10k_pci_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ath10k_pci_qca99x0_targ_cpu_to_ce_addr(struct ath10k *ar, u32 addr)
{
	u32 val = 0, region = addr & 0xfffff;

	val = ath10k_pci_read32(ar, PCIE_BAR_REG_ADDRESS);
	val |= 0x100000 | region;
	return val;
}