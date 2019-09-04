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
struct device {int dummy; } ;

/* Variables and functions */
 int _qcom_cc_register_board_clk (struct device*,char const*,char const*,unsigned long,int) ; 

int qcom_cc_register_board_clk(struct device *dev, const char *path,
			       const char *name, unsigned long rate)
{
	bool add_factor = true;

	/*
	 * TODO: The RPM clock driver currently does not support the xo clock.
	 * When xo is added to the RPM clock driver, we should change this
	 * function to skip registration of xo factor clocks.
	 */

	return _qcom_cc_register_board_clk(dev, path, name, rate, add_factor);
}