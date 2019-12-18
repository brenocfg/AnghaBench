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
struct ath10k_pci {int /*<<< orphan*/ * pipe_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int CE_COUNT ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_post_pipe (int /*<<< orphan*/ *) ; 

void ath10k_pci_rx_post(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	int i;

	for (i = 0; i < CE_COUNT; i++)
		ath10k_pci_rx_post_pipe(&ar_pci->pipe_info[i]);
}