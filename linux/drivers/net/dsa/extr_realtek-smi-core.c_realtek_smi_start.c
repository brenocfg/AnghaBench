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
struct realtek_smi {int /*<<< orphan*/  mdio; int /*<<< orphan*/  mdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realtek_smi_clk_delay (struct realtek_smi*) ; 

__attribute__((used)) static void realtek_smi_start(struct realtek_smi *smi)
{
	/* Set GPIO pins to output mode, with initial state:
	 * SCK = 0, SDA = 1
	 */
	gpiod_direction_output(smi->mdc, 0);
	gpiod_direction_output(smi->mdio, 1);
	realtek_smi_clk_delay(smi);

	/* CLK 1: 0 -> 1, 1 -> 0 */
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);

	/* CLK 2: */
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 1);
}