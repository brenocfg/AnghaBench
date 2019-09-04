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
struct btmtkuart_dev {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKUART_TX_STATE_ACTIVE ; 
 int /*<<< orphan*/  BTMTKUART_TX_STATE_WAKEUP ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btmtkuart_tx_wakeup(struct btmtkuart_dev *bdev)
{
	if (test_and_set_bit(BTMTKUART_TX_STATE_ACTIVE, &bdev->tx_state))
		set_bit(BTMTKUART_TX_STATE_WAKEUP, &bdev->tx_state);

	schedule_work(&bdev->tx_work);
}