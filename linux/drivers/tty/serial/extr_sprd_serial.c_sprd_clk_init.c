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
struct uart_port {size_t line; int /*<<< orphan*/  dev; int /*<<< orphan*/  uartclk; } ;
struct sprd_uart_port {struct clk* clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SPRD_DEFAULT_SOURCE_CLK ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 scalar_t__ clk_set_parent (struct clk*,struct clk*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 struct sprd_uart_port** sprd_port ; 
 int /*<<< orphan*/  sprd_uart_is_console (struct uart_port*) ; 

__attribute__((used)) static int sprd_clk_init(struct uart_port *uport)
{
	struct clk *clk_uart, *clk_parent;
	struct sprd_uart_port *u = sprd_port[uport->line];

	clk_uart = devm_clk_get(uport->dev, "uart");
	if (IS_ERR(clk_uart)) {
		dev_warn(uport->dev, "uart%d can't get uart clock\n",
			 uport->line);
		clk_uart = NULL;
	}

	clk_parent = devm_clk_get(uport->dev, "source");
	if (IS_ERR(clk_parent)) {
		dev_warn(uport->dev, "uart%d can't get source clock\n",
			 uport->line);
		clk_parent = NULL;
	}

	if (!clk_uart || clk_set_parent(clk_uart, clk_parent))
		uport->uartclk = SPRD_DEFAULT_SOURCE_CLK;
	else
		uport->uartclk = clk_get_rate(clk_uart);

	u->clk = devm_clk_get(uport->dev, "enable");
	if (IS_ERR(u->clk)) {
		if (PTR_ERR(u->clk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_warn(uport->dev, "uart%d can't get enable clock\n",
			uport->line);

		/* To keep console alive even if the error occurred */
		if (!sprd_uart_is_console(uport))
			return PTR_ERR(u->clk);

		u->clk = NULL;
	}

	return 0;
}