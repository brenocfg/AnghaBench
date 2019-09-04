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
struct realtek_smi {int /*<<< orphan*/  mdc; int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realtek_smi_clk_delay (struct realtek_smi*) ; 

__attribute__((used)) static void realtek_smi_write_bits(struct realtek_smi *smi, u32 data, u32 len)
{
	for (; len > 0; len--) {
		realtek_smi_clk_delay(smi);

		/* Prepare data */
		gpiod_set_value(smi->mdio, !!(data & (1 << (len - 1))));
		realtek_smi_clk_delay(smi);

		/* Clocking */
		gpiod_set_value(smi->mdc, 1);
		realtek_smi_clk_delay(smi);
		gpiod_set_value(smi->mdc, 0);
	}
}