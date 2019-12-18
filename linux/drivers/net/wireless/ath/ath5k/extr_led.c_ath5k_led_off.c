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
struct ath5k_hw {int /*<<< orphan*/  led_on; int /*<<< orphan*/  led_pin; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_STAT_LEDSOFT ; 
 int /*<<< orphan*/  ath5k_hw_set_gpio (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath5k_led_off(struct ath5k_hw *ah)
{
	if (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		return;
	ath5k_hw_set_gpio(ah, ah->led_pin, !ah->led_on);
}