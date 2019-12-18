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
struct ath5k_hw {int /*<<< orphan*/  tx_led; int /*<<< orphan*/  rx_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_unregister_led (int /*<<< orphan*/ *) ; 

void ath5k_unregister_leds(struct ath5k_hw *ah)
{
	ath5k_unregister_led(&ah->rx_led);
	ath5k_unregister_led(&ah->tx_led);
}