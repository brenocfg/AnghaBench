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
struct ath10k {int /*<<< orphan*/  htt; int /*<<< orphan*/  workqueue_aux; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_coredump_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_debug_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_mac_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_free_host_mem (struct ath10k*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

void ath10k_core_destroy(struct ath10k *ar)
{
	flush_workqueue(ar->workqueue);
	destroy_workqueue(ar->workqueue);

	flush_workqueue(ar->workqueue_aux);
	destroy_workqueue(ar->workqueue_aux);

	ath10k_debug_destroy(ar);
	ath10k_coredump_destroy(ar);
	ath10k_htt_tx_destroy(&ar->htt);
	ath10k_wmi_free_host_mem(ar);
	ath10k_mac_destroy(ar);
}