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
struct at91_usart_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  MR ; 
 int US_DISABLE ; 
 int US_INIT ; 
 int US_RESET ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91_usart_spi_init(struct at91_usart_spi *aus)
{
	at91_usart_spi_writel(aus, MR, US_INIT);
	at91_usart_spi_writel(aus, CR, US_RESET | US_DISABLE);
}