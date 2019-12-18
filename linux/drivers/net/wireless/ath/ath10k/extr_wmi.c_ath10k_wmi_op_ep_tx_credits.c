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
struct TYPE_2__ {int /*<<< orphan*/  tx_credits_wq; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_wmi_tx_beacons_nowait (struct ath10k*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_wmi_op_ep_tx_credits(struct ath10k *ar)
{
	/* try to send pending beacons first. they take priority */
	ath10k_wmi_tx_beacons_nowait(ar);

	wake_up(&ar->wmi.tx_credits_wq);
}