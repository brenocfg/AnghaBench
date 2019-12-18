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
struct ath10k {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_ce_enable_interrupts (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_pci_enable_legacy_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_post (struct ath10k*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_ahb_hif_start(struct ath10k *ar)
{
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot ahb hif start\n");

	napi_enable(&ar->napi);
	ath10k_ce_enable_interrupts(ar);
	ath10k_pci_enable_legacy_irq(ar);

	ath10k_pci_rx_post(ar);

	return 0;
}