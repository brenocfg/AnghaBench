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
struct uart_port {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct uart_port* s3c24xx_dev_to_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c24xx_serial_cpufreq_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_uart_drv ; 
 int /*<<< orphan*/  to_ourport (struct uart_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 
 int /*<<< orphan*/  uart_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c24xx_serial_remove(struct platform_device *dev)
{
	struct uart_port *port = s3c24xx_dev_to_port(&dev->dev);

	if (port) {
		s3c24xx_serial_cpufreq_deregister(to_ourport(port));
		uart_remove_one_port(&s3c24xx_uart_drv, port);
	}

	uart_unregister_driver(&s3c24xx_uart_drv);

	return 0;
}