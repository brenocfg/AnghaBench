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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_pci_buffer_cleanup (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_retry_sync (struct ath10k*) ; 

void ath10k_pci_flush(struct ath10k *ar)
{
	ath10k_pci_rx_retry_sync(ar);
	ath10k_pci_buffer_cleanup(ar);
}