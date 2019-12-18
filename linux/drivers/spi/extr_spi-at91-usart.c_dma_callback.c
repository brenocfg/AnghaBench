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
struct at91_usart_spi {int /*<<< orphan*/  xfer_completion; scalar_t__ current_rx_remaining_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  US_IR_RXRDY ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static void dma_callback(void *data)
{
	struct spi_controller   *ctlr = data;
	struct at91_usart_spi   *aus = spi_master_get_devdata(ctlr);

	at91_usart_spi_writel(aus, IER, US_IR_RXRDY);
	aus->current_rx_remaining_bytes = 0;
	complete(&aus->xfer_completion);
}