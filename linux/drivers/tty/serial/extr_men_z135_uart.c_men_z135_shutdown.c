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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct men_z135_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEN_Z135_ALL_IRQS ; 
 int /*<<< orphan*/  MEN_Z135_CONF_REG ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct men_z135_port*) ; 
 int /*<<< orphan*/  men_z135_reg_clr (struct men_z135_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 

__attribute__((used)) static void men_z135_shutdown(struct uart_port *port)
{
	struct men_z135_port *uart = to_men_z135(port);
	u32 conf_reg = 0;

	conf_reg |= MEN_Z135_ALL_IRQS;

	men_z135_reg_clr(uart, MEN_Z135_CONF_REG, conf_reg);

	free_irq(uart->port.irq, uart);
}