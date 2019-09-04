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
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 scalar_t__* _loongson_uart_base ; 
 int serial_in (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (unsigned char*,int /*<<< orphan*/ ,char) ; 

void prom_putchar(char c)
{
	int timeout;
	unsigned char *uart_base;

	uart_base = (unsigned char *)_loongson_uart_base[0];
	timeout = 1024;

	while (((serial_in(uart_base, UART_LSR) & UART_LSR_THRE) == 0) &&
			(timeout-- > 0))
		;

	serial_out(uart_base, UART_TX, c);
}