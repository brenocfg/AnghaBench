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
struct spi_transfer {int /*<<< orphan*/  speed_hz; } ;
struct at91_usart_spi {int /*<<< orphan*/  spi_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRGR ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
at91_usart_spi_set_xfer_speed(struct at91_usart_spi *aus,
			      struct spi_transfer *xfer)
{
	at91_usart_spi_writel(aus, BRGR,
			      DIV_ROUND_UP(aus->spi_clk, xfer->speed_hz));
}