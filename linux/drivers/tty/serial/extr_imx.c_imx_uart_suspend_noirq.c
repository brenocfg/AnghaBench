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
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct imx_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  imx_uart_save_context (struct imx_port*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (struct device*) ; 

__attribute__((used)) static int imx_uart_suspend_noirq(struct device *dev)
{
	struct imx_port *sport = dev_get_drvdata(dev);

	imx_uart_save_context(sport);

	clk_disable(sport->clk_ipg);

	pinctrl_pm_select_sleep_state(dev);

	return 0;
}