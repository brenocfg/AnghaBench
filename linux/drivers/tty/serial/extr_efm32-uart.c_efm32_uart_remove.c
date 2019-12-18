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
struct platform_device {int dummy; } ;
struct TYPE_2__ {unsigned int line; } ;
struct efm32_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** efm32_uart_ports ; 
 int /*<<< orphan*/  efm32_uart_reg ; 
 int /*<<< orphan*/  kfree (struct efm32_uart_port*) ; 
 struct efm32_uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int efm32_uart_remove(struct platform_device *pdev)
{
	struct efm32_uart_port *efm_port = platform_get_drvdata(pdev);
	unsigned int line = efm_port->port.line;

	uart_remove_one_port(&efm32_uart_reg, &efm_port->port);

	if (line >= 0 && line < ARRAY_SIZE(efm32_uart_ports))
		efm32_uart_ports[line] = NULL;

	kfree(efm_port);

	return 0;
}