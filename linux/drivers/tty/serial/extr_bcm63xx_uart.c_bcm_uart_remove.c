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
struct uart_port {int dummy; } ;
struct platform_device {size_t id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_uart_driver ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 TYPE_1__* ports ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int bcm_uart_remove(struct platform_device *pdev)
{
	struct uart_port *port;

	port = platform_get_drvdata(pdev);
	uart_remove_one_port(&bcm_uart_driver, port);
	/* mark port as free */
	ports[pdev->id].membase = NULL;
	return 0;
}