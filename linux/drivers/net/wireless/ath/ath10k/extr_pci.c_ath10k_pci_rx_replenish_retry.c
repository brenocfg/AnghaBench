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
struct timer_list {int dummy; } ;
struct ath10k_pci {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_pci* ar_pci ; 
 int /*<<< orphan*/  ath10k_pci_rx_post (struct ath10k*) ; 
 struct ath10k_pci* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_post_retry ; 

void ath10k_pci_rx_replenish_retry(struct timer_list *t)
{
	struct ath10k_pci *ar_pci = from_timer(ar_pci, t, rx_post_retry);
	struct ath10k *ar = ar_pci->ar;

	ath10k_pci_rx_post(ar);
}