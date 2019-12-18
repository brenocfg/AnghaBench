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
typedef  scalar_t__ u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ CORE_CTRL_ADDRESS ; 
 scalar_t__ CORE_CTRL_CPU_INTR_MASK ; 
 scalar_t__ SOC_CORE_BASE_ADDRESS ; 
 scalar_t__ ath10k_pci_read32 (struct ath10k*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ath10k_pci_wake_target_cpu(struct ath10k *ar)
{
	u32 addr, val;

	addr = SOC_CORE_BASE_ADDRESS + CORE_CTRL_ADDRESS;
	val = ath10k_pci_read32(ar, addr);
	val |= CORE_CTRL_CPU_INTR_MASK;
	ath10k_pci_write32(ar, addr, val);

	return 0;
}