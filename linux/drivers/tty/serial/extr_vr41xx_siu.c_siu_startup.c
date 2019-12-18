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
struct uart_port {scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  irq; int /*<<< orphan*/ * membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIUINT_ALL ; 
 int ENODEV ; 
 scalar_t__ PORT_VR41XX_DSIU ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  siu_clear_fifo (struct uart_port*) ; 
 int /*<<< orphan*/  siu_interrupt ; 
 int siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siu_set_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siu_type_name (struct uart_port*) ; 
 int /*<<< orphan*/  siu_write (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vr41xx_enable_dsiuint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siu_startup(struct uart_port *port)
{
	int retval;

	if (port->membase == NULL)
		return -ENODEV;

	siu_clear_fifo(port);

	(void)siu_read(port, UART_LSR);
	(void)siu_read(port, UART_RX);
	(void)siu_read(port, UART_IIR);
	(void)siu_read(port, UART_MSR);

	if (siu_read(port, UART_LSR) == 0xff)
		return -ENODEV;

	retval = request_irq(port->irq, siu_interrupt, 0, siu_type_name(port), port);
	if (retval)
		return retval;

	if (port->type == PORT_VR41XX_DSIU)
		vr41xx_enable_dsiuint(DSIUINT_ALL);

	siu_write(port, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irq(&port->lock);
	siu_set_mctrl(port, port->mctrl);
	spin_unlock_irq(&port->lock);

	siu_write(port, UART_IER, UART_IER_RLSI | UART_IER_RDI);

	(void)siu_read(port, UART_LSR);
	(void)siu_read(port, UART_RX);
	(void)siu_read(port, UART_IIR);
	(void)siu_read(port, UART_MSR);

	return 0;
}