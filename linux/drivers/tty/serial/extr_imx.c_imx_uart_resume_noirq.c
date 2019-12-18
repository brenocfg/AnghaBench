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
struct imx_port {int /*<<< orphan*/  clk_ipg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct imx_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  imx_uart_restore_context (struct imx_port*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (struct device*) ; 

__attribute__((used)) static int imx_uart_resume_noirq(struct device *dev)
{
	struct imx_port *sport = dev_get_drvdata(dev);
	int ret;

	pinctrl_pm_select_default_state(dev);

	ret = clk_enable(sport->clk_ipg);
	if (ret)
		return ret;

	imx_uart_restore_context(sport);

	return 0;
}