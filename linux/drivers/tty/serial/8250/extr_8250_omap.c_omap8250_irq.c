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
struct uart_8250_port {scalar_t__ dma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  UART_IIR ; 
 int omap_8250_dma_handle_irq (struct uart_port*) ; 
 int serial8250_handle_irq (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t omap8250_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned int iir;
	int ret;

#ifdef CONFIG_SERIAL_8250_DMA
	if (up->dma) {
		ret = omap_8250_dma_handle_irq(port);
		return IRQ_RETVAL(ret);
	}
#endif

	serial8250_rpm_get(up);
	iir = serial_port_in(port, UART_IIR);
	ret = serial8250_handle_irq(port, iir);
	serial8250_rpm_put(up);

	return IRQ_RETVAL(ret);
}