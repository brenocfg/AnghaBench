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
struct uart_port {int /*<<< orphan*/  uartclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 struct clk* meson_uart_probe_clock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_uart_probe_clocks_legacy(struct platform_device *pdev,
					  struct uart_port *port)
{
	struct clk *clk = NULL;

	clk = meson_uart_probe_clock(&pdev->dev, NULL);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	port->uartclk = clk_get_rate(clk);

	return 0;
}