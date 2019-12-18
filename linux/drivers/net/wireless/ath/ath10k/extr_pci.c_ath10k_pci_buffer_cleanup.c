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
struct ath10k_pci_pipe {int dummy; } ;
struct ath10k_pci {struct ath10k_pci_pipe* pipe_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int CE_COUNT ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_pipe_cleanup (struct ath10k_pci_pipe*) ; 
 int /*<<< orphan*/  ath10k_pci_tx_pipe_cleanup (struct ath10k_pci_pipe*) ; 

__attribute__((used)) static void ath10k_pci_buffer_cleanup(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	int pipe_num;

	for (pipe_num = 0; pipe_num < CE_COUNT; pipe_num++) {
		struct ath10k_pci_pipe *pipe_info;

		pipe_info = &ar_pci->pipe_info[pipe_num];
		ath10k_pci_rx_pipe_cleanup(pipe_info);
		ath10k_pci_tx_pipe_cleanup(pipe_info);
	}
}