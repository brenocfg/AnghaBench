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
typedef  scalar_t__ u32 ;
struct realtek_smi {int /*<<< orphan*/  mdio; int /*<<< orphan*/  mdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realtek_smi_clk_delay (struct realtek_smi*) ; 

__attribute__((used)) static void realtek_smi_read_bits(struct realtek_smi *smi, u32 len, u32 *data)
{
	gpiod_direction_input(smi->mdio);

	for (*data = 0; len > 0; len--) {
		u32 u;

		realtek_smi_clk_delay(smi);

		/* Clocking */
		gpiod_set_value(smi->mdc, 1);
		realtek_smi_clk_delay(smi);
		u = !!gpiod_get_value(smi->mdio);
		gpiod_set_value(smi->mdc, 0);

		*data |= (u << (len - 1));
	}

	gpiod_direction_output(smi->mdio, 0);
}