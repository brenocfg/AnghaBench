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
 int /*<<< orphan*/  ath10k_pci_ce_deinit (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_free_pipes (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_retry_sync (struct ath10k*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

void ath10k_pci_release_resource(struct ath10k *ar)
{
	ath10k_pci_rx_retry_sync(ar);
	netif_napi_del(&ar->napi);
	ath10k_pci_ce_deinit(ar);
	ath10k_pci_free_pipes(ar);
}