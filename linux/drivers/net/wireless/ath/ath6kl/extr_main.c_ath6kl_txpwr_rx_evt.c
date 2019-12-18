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
typedef  int /*<<< orphan*/  u8 ;
struct ath6kl {int /*<<< orphan*/  event_wq; int /*<<< orphan*/  tx_pwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ath6kl_txpwr_rx_evt(void *devt, u8 tx_pwr)
{
	struct ath6kl *ar = (struct ath6kl *) devt;

	ar->tx_pwr = tx_pwr;
	wake_up(&ar->event_wq);
}