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
struct mxic_spi {int /*<<< orphan*/  send_dly_clk; int /*<<< orphan*/  send_clk; } ;

/* Variables and functions */
 int clk_set_phase (int /*<<< orphan*/ ,int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mxic_spi_set_input_delay_dqs (struct mxic_spi*,int) ; 

__attribute__((used)) static int mxic_spi_clk_setup(struct mxic_spi *mxic, unsigned long freq)
{
	int ret;

	ret = clk_set_rate(mxic->send_clk, freq);
	if (ret)
		return ret;

	ret = clk_set_rate(mxic->send_dly_clk, freq);
	if (ret)
		return ret;

	/*
	 * A constant delay range from 0x0 ~ 0x1F for input delay,
	 * the unit is 78 ps, the max input delay is 2.418 ns.
	 */
	mxic_spi_set_input_delay_dqs(mxic, 0xf);

	/*
	 * Phase degree = 360 * freq * output-delay
	 * where output-delay is a constant value 1 ns in FPGA.
	 *
	 * Get Phase degree = 360 * freq * 1 ns
	 *                  = 360 * freq * 1 sec / 1000000000
	 *                  = 9 * freq / 25000000
	 */
	ret = clk_set_phase(mxic->send_dly_clk, 9 * freq / 25000000);
	if (ret)
		return ret;

	return 0;
}