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
struct uart_port {struct clk* private_data; } ;
struct platform_device {size_t id; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 struct uart_port* mlb_usio_ports ; 
 int /*<<< orphan*/  mlb_usio_uart_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int mlb_usio_remove(struct platform_device *pdev)
{
	struct uart_port *port = &mlb_usio_ports[pdev->id];
	struct clk *clk = port->private_data;

	uart_remove_one_port(&mlb_usio_uart_driver, port);
	clk_disable_unprepare(clk);

	return 0;
}