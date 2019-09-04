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
struct hns_mac_cb {int /*<<< orphan*/  cpld_led_value; int /*<<< orphan*/  cpld_ctrl_reg; int /*<<< orphan*/  cpld_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_LED_DEFAULT_VALUE ; 
 int /*<<< orphan*/  dsaf_write_syscon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpld_led_reset(struct hns_mac_cb *mac_cb)
{
	if (!mac_cb || !mac_cb->cpld_ctrl)
		return;

	dsaf_write_syscon(mac_cb->cpld_ctrl, mac_cb->cpld_ctrl_reg,
			  CPLD_LED_DEFAULT_VALUE);
	mac_cb->cpld_led_value = CPLD_LED_DEFAULT_VALUE;
}