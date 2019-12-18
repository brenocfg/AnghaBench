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
 int /*<<< orphan*/  GPIO_INPUT_AUX1 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_AUX1 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_AUX2 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  GPIO_OUTPUT_VAL ; 
 int /*<<< orphan*/  OLPC_GPIO_SMB_CLK ; 
 int /*<<< orphan*/  OLPC_GPIO_SMB_DATA ; 
 int /*<<< orphan*/  cs5535_gpio_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dcon_wiggle_xo_1(void)
{
	int x;

	/*
	 * According to HiMax, when powering the DCON up we should hold
	 * SMB_DATA high for 8 SMB_CLK cycles.  This will force the DCON
	 * state machine to reset to a (sane) initial state.  Mitch Bradley
	 * did some testing and discovered that holding for 16 SMB_CLK cycles
	 * worked a lot more reliably, so that's what we do here.
	 *
	 * According to the cs5536 spec, to set GPIO14 to SMB_CLK we must
	 * simultaneously set AUX1 IN/OUT to GPIO14; ditto for SMB_DATA and
	 * GPIO15.
	 */
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_VAL);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_ENABLE);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_ENABLE);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX2);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX2);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_INPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_INPUT_AUX1);

	for (x = 0; x < 16; x++) {
		udelay(5);
		cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
		udelay(5);
		cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
	}
	udelay(5);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_INPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_INPUT_AUX1);
}