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
struct realtek_smi {int /*<<< orphan*/  mdc; int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realtek_smi_clk_delay (struct realtek_smi*) ; 

__attribute__((used)) static void realtek_smi_stop(struct realtek_smi *smi)
{
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 0);
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);

	/* Add a click */
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);

	/* Set GPIO pins to input mode */
	gpiod_direction_input(smi->mdio);
	gpiod_direction_input(smi->mdc);
}