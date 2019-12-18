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
struct TYPE_2__ {int /*<<< orphan*/  fw_cold_reset_counter; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  SOC_GLOBAL_RESET_ADDRESS ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_pci_reg_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_pci_reg_write32 (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_pci_cold_reset(struct ath10k *ar)
{
	u32 val;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cold reset\n");

	spin_lock_bh(&ar->data_lock);

	ar->stats.fw_cold_reset_counter++;

	spin_unlock_bh(&ar->data_lock);

	/* Put Target, including PCIe, into RESET. */
	val = ath10k_pci_reg_read32(ar, SOC_GLOBAL_RESET_ADDRESS);
	val |= 1;
	ath10k_pci_reg_write32(ar, SOC_GLOBAL_RESET_ADDRESS, val);

	/* After writing into SOC_GLOBAL_RESET to put device into
	 * reset and pulling out of reset pcie may not be stable
	 * for any immediate pcie register access and cause bus error,
	 * add delay before any pcie access request to fix this issue.
	 */
	msleep(20);

	/* Pull Target, including PCIe, out of RESET. */
	val &= ~1;
	ath10k_pci_reg_write32(ar, SOC_GLOBAL_RESET_ADDRESS, val);

	msleep(20);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cold reset complete\n");

	return 0;
}