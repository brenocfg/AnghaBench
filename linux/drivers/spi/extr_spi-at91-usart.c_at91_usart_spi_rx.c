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
struct at91_usart_spi {int current_rx_remaining_bytes; TYPE_1__* current_transfer; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RHR ; 
 int /*<<< orphan*/  at91_usart_spi_readb (struct at91_usart_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void at91_usart_spi_rx(struct at91_usart_spi *aus)
{
	int len = aus->current_transfer->len;
	int remaining = aus->current_rx_remaining_bytes;
	u8  *rx_buf = aus->current_transfer->rx_buf;

	if (!remaining)
		return;

	rx_buf[len - remaining] = at91_usart_spi_readb(aus, RHR);
	aus->current_rx_remaining_bytes--;
}