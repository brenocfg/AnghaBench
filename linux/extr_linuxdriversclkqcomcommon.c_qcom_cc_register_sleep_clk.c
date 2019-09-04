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
 int _qcom_cc_register_board_clk (struct device*,char*,char*,int,int) ; 

int qcom_cc_register_sleep_clk(struct device *dev)
{
	return _qcom_cc_register_board_clk(dev, "sleep_clk", "sleep_clk_src",
					   32768, true);
}