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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct il_priv {int /*<<< orphan*/  tx_flush; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 scalar_t__ TX_STATUS_FAIL_RFKILL_FLUSH ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il4965_check_abort_status(struct il_priv *il, u8 frame_count, u32 status)
{
	if (frame_count == 1 && status == TX_STATUS_FAIL_RFKILL_FLUSH) {
		IL_ERR("Tx flush command to flush out all frames\n");
		if (!test_bit(S_EXIT_PENDING, &il->status))
			queue_work(il->workqueue, &il->tx_flush);
	}
}