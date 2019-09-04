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

/* Variables and functions */
 int /*<<< orphan*/  DSPIC_RST_B ; 
 int /*<<< orphan*/  POWER_EN ; 
 int /*<<< orphan*/  TRSLAT_RST_B ; 
 int /*<<< orphan*/  TRSLAT_SRC_CHOICE ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_export (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void smartbot_resets_init(void)
{
	if (!gpio_request(POWER_EN, "power-enable")) {
		gpio_direction_output(POWER_EN, 0);
		gpio_export(POWER_EN, false);
	}

	if (!gpio_request(DSPIC_RST_B, "dspic-rst")) {
		gpio_direction_output(DSPIC_RST_B, 0);
		gpio_export(DSPIC_RST_B, false);
	}

	if (!gpio_request(TRSLAT_RST_B, "translator-rst")) {
		gpio_direction_output(TRSLAT_RST_B, 0);
		gpio_export(TRSLAT_RST_B, false);
	}

	if (!gpio_request(TRSLAT_SRC_CHOICE, "translator-src-choice")) {
		gpio_direction_output(TRSLAT_SRC_CHOICE, 0);
		gpio_export(TRSLAT_SRC_CHOICE, false);
	}
}