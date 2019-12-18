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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_ICLR ; 
 int /*<<< orphan*/  SPRD_IEN ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  serial_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_release_dma (struct uart_port*) ; 

__attribute__((used)) static void sprd_shutdown(struct uart_port *port)
{
	sprd_release_dma(port);
	serial_out(port, SPRD_IEN, 0);
	serial_out(port, SPRD_ICLR, ~0);
	devm_free_irq(port->dev, port->irq, port);
}