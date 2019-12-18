#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  membase; int /*<<< orphan*/  dev; int /*<<< orphan*/  mapbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  membase; } ;
struct efm32_uart_port {int /*<<< orphan*/  clk; TYPE_1__ port; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm_debug (struct efm32_uart_port*,char*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct efm32_uart_port* to_efm_port (struct uart_port*) ; 

__attribute__((used)) static int efm32_uart_request_port(struct uart_port *port)
{
	struct efm32_uart_port *efm_port = to_efm_port(port);
	int ret;

	port->membase = ioremap(port->mapbase, 60);
	if (!efm_port->port.membase) {
		ret = -ENOMEM;
		efm_debug(efm_port, "failed to remap\n");
		goto err_ioremap;
	}

	efm_port->clk = clk_get(port->dev, NULL);
	if (IS_ERR(efm_port->clk)) {
		ret = PTR_ERR(efm_port->clk);
		efm_debug(efm_port, "failed to get clock\n");
		goto err_clk_get;
	}

	ret = clk_prepare(efm_port->clk);
	if (ret) {
		clk_put(efm_port->clk);
err_clk_get:

		iounmap(port->membase);
err_ioremap:
		return ret;
	}
	return 0;
}