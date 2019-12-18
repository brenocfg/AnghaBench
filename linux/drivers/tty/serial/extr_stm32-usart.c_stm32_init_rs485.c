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
struct serial_rs485 {scalar_t__ delay_rts_after_send; scalar_t__ delay_rts_before_send; scalar_t__ flags; } ;
struct uart_port {struct serial_rs485 rs485; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  uart_get_rs485_mode (TYPE_1__*,struct serial_rs485*) ; 

__attribute__((used)) static int stm32_init_rs485(struct uart_port *port,
			    struct platform_device *pdev)
{
	struct serial_rs485 *rs485conf = &port->rs485;

	rs485conf->flags = 0;
	rs485conf->delay_rts_before_send = 0;
	rs485conf->delay_rts_after_send = 0;

	if (!pdev->dev.of_node)
		return -ENODEV;

	uart_get_rs485_mode(&pdev->dev, rs485conf);

	return 0;
}