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
struct rtl_led {int ledpin; int ledon; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rtl_led_pin { ____Placeholder_rtl_led_pin } rtl_led_pin ;

/* Variables and functions */

__attribute__((used)) static void _rtl88ee_init_led(struct ieee80211_hw *hw,
			      struct rtl_led *pled, enum rtl_led_pin ledpin)
{
	pled->hw = hw;
	pled->ledpin = ledpin;
	pled->ledon = false;
}