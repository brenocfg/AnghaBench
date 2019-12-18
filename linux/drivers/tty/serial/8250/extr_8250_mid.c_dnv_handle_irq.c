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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {struct mid8250* private_data; } ;
struct uart_8250_port {int dummy; } ;
struct mid8250 {int /*<<< orphan*/  dma_chip; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  INTEL_MID_UART_FISR ; 
 int IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  UART_IIR ; 
 int hsu_dma_do_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hsu_dma_get_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int serial8250_handle_irq (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_rx_dma_flush (struct uart_8250_port*) ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static int dnv_handle_irq(struct uart_port *p)
{
	struct mid8250 *mid = p->private_data;
	struct uart_8250_port *up = up_to_u8250p(p);
	unsigned int fisr = serial_port_in(p, INTEL_MID_UART_FISR);
	u32 status;
	int ret = 0;
	int err;

	if (fisr & BIT(2)) {
		err = hsu_dma_get_status(&mid->dma_chip, 1, &status);
		if (err > 0) {
			serial8250_rx_dma_flush(up);
			ret |= 1;
		} else if (err == 0)
			ret |= hsu_dma_do_irq(&mid->dma_chip, 1, status);
	}
	if (fisr & BIT(1)) {
		err = hsu_dma_get_status(&mid->dma_chip, 0, &status);
		if (err > 0)
			ret |= 1;
		else if (err == 0)
			ret |= hsu_dma_do_irq(&mid->dma_chip, 0, status);
	}
	if (fisr & BIT(0))
		ret |= serial8250_handle_irq(p, serial_port_in(p, UART_IIR));
	return IRQ_RETVAL(ret);
}