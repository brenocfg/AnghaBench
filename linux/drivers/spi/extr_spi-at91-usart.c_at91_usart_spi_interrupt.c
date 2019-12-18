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
struct spi_controller {int dummy; } ;
struct at91_usart_spi {int xfer_failed; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int US_IR_OVRE ; 
 int US_IR_RXRDY ; 
 scalar_t__ at91_usart_spi_check_overrun (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_read_status (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_rx (struct at91_usart_spi*) ; 
 scalar_t__ at91_usart_spi_rx_ready (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t at91_usart_spi_interrupt(int irq, void *dev_id)
{
	struct spi_controller *controller = dev_id;
	struct at91_usart_spi *aus = spi_master_get_devdata(controller);

	spin_lock(&aus->lock);
	at91_usart_spi_read_status(aus);

	if (at91_usart_spi_check_overrun(aus)) {
		aus->xfer_failed = true;
		at91_usart_spi_writel(aus, IDR, US_IR_OVRE | US_IR_RXRDY);
		spin_unlock(&aus->lock);
		return IRQ_HANDLED;
	}

	if (at91_usart_spi_rx_ready(aus)) {
		at91_usart_spi_rx(aus);
		spin_unlock(&aus->lock);
		return IRQ_HANDLED;
	}

	spin_unlock(&aus->lock);

	return IRQ_NONE;
}