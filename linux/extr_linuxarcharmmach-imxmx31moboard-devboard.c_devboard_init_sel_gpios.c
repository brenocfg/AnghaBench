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
 int /*<<< orphan*/  SEL0 ; 
 int /*<<< orphan*/  SEL1 ; 
 int /*<<< orphan*/  SEL2 ; 
 int /*<<< orphan*/  SEL3 ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_export (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void devboard_init_sel_gpios(void)
{
	if (!gpio_request(SEL0, "sel0")) {
		gpio_direction_input(SEL0);
		gpio_export(SEL0, true);
	}

	if (!gpio_request(SEL1, "sel1")) {
		gpio_direction_input(SEL1);
		gpio_export(SEL1, true);
	}

	if (!gpio_request(SEL2, "sel2")) {
		gpio_direction_input(SEL2);
		gpio_export(SEL2, true);
	}

	if (!gpio_request(SEL3, "sel3")) {
		gpio_direction_input(SEL3);
		gpio_export(SEL3, true);
	}
}