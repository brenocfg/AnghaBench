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
typedef  int /*<<< orphan*/  u8 ;
struct at91_usart_spi {unsigned int current_tx_remaining_bytes; TYPE_1__* current_transfer; } ;
struct TYPE_2__ {unsigned int len; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR ; 
 scalar_t__ at91_usart_spi_tx_ready (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_writeb (struct at91_usart_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void at91_usart_spi_tx(struct at91_usart_spi *aus)
{
	unsigned int len = aus->current_transfer->len;
	unsigned int remaining = aus->current_tx_remaining_bytes;
	const u8  *tx_buf = aus->current_transfer->tx_buf;

	if (!remaining)
		return;

	if (at91_usart_spi_tx_ready(aus)) {
		at91_usart_spi_writeb(aus, THR, tx_buf[len - remaining]);
		aus->current_tx_remaining_bytes--;
	}
}