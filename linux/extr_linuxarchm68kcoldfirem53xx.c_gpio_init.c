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

/* Variables and functions */
 int /*<<< orphan*/  MCFGPIO_PAR_TIMER ; 
 int /*<<< orphan*/  MCFGPIO_PAR_UART ; 
 int /*<<< orphan*/  MCFGPIO_PCLRR_TIMER ; 
 int /*<<< orphan*/  MCFGPIO_PDDR_TIMER ; 
 int MCF_GPIO_PAR_UART_PAR_URXD0 ; 
 int MCF_GPIO_PAR_UART_PAR_UTXD0 ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

void gpio_init(void)
{
	/* Enable UART0 pins */
	writew(MCF_GPIO_PAR_UART_PAR_URXD0 | MCF_GPIO_PAR_UART_PAR_UTXD0,
		MCFGPIO_PAR_UART);

	/*
	 * Initialize TIN3 as a GPIO output to enable the write
	 * half of the latch.
	 */
	writeb(0x00, MCFGPIO_PAR_TIMER);
	writeb(0x08, MCFGPIO_PDDR_TIMER);
	writeb(0x00, MCFGPIO_PCLRR_TIMER);
}