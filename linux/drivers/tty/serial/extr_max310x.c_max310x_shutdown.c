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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct max310x_port {TYPE_1__* devtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power ) (struct uart_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX310X_IRQEN_REG ; 
 struct max310x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_port_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max310x_shutdown(struct uart_port *port)
{
	struct max310x_port *s = dev_get_drvdata(port->dev);

	/* Disable all interrupts */
	max310x_port_write(port, MAX310X_IRQEN_REG, 0);

	s->devtype->power(port, 0);
}