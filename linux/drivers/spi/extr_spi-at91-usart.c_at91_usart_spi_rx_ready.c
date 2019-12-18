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
typedef  int u32 ;
struct at91_usart_spi {int status; } ;

/* Variables and functions */
 int US_IR_RXRDY ; 

__attribute__((used)) static inline u32 at91_usart_spi_rx_ready(struct at91_usart_spi *aus)
{
	return aus->status & US_IR_RXRDY;
}