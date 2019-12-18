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
struct ath10k_pci {int ps_awake; scalar_t__ mem; int /*<<< orphan*/  ps_wake_refcount; int /*<<< orphan*/  ps_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_PCI_PS ; 
 scalar_t__ PCIE_LOCAL_BASE_ADDRESS ; 
 scalar_t__ PCIE_SOC_WAKE_ADDRESS ; 
 int /*<<< orphan*/  PCIE_SOC_WAKE_RESET ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ath10k_pci_sleep(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	lockdep_assert_held(&ar_pci->ps_lock);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps sleep reg refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	iowrite32(PCIE_SOC_WAKE_RESET,
		  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
		  PCIE_SOC_WAKE_ADDRESS);
	ar_pci->ps_awake = false;
}