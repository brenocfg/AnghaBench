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
struct TYPE_2__ {size_t line; } ;
struct sprd_uart_port {TYPE_1__ port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sprd_uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ ** sprd_port ; 
 int /*<<< orphan*/  sprd_ports_num ; 
 int /*<<< orphan*/  sprd_rx_free_buf (struct sprd_uart_port*) ; 
 int /*<<< orphan*/  sprd_uart_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uart_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_remove(struct platform_device *dev)
{
	struct sprd_uart_port *sup = platform_get_drvdata(dev);

	if (sup) {
		uart_remove_one_port(&sprd_uart_driver, &sup->port);
		sprd_port[sup->port.line] = NULL;
		sprd_ports_num--;
	}

	if (!sprd_ports_num)
		uart_unregister_driver(&sprd_uart_driver);

	sprd_rx_free_buf(sup);

	return 0;
}