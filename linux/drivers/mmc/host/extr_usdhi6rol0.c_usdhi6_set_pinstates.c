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
struct usdhi6_host {int /*<<< orphan*/  pins_default; int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  pins_uhs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_SIGNAL_VOLTAGE_120 129 
#define  MMC_SIGNAL_VOLTAGE_180 128 
 int pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usdhi6_set_pinstates(struct usdhi6_host *host, int voltage)
{
	if (IS_ERR(host->pins_uhs))
		return 0;

	switch (voltage) {
	case MMC_SIGNAL_VOLTAGE_180:
	case MMC_SIGNAL_VOLTAGE_120:
		return pinctrl_select_state(host->pinctrl,
					    host->pins_uhs);

	default:
		return pinctrl_select_state(host->pinctrl,
					    host->pins_default);
	}
}