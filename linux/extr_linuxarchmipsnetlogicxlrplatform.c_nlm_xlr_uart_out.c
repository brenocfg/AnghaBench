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
typedef  scalar_t__ uint64_t ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int UART_MCR ; 
 int UART_MSR ; 
 int /*<<< orphan*/  nlm_write_reg (scalar_t__,int,int) ; 

__attribute__((used)) static void nlm_xlr_uart_out(struct uart_port *p, int offset, int value)
{
	uint64_t uartbase;

	/* sign extend to 64 bits, if needed */
	uartbase = (uint64_t)(long)p->membase;

	/* See XLR/XLS errata */
	if (offset == UART_MSR)
		value ^= 0xF0;
	else if (offset == UART_MCR)
		value ^= 0x3;

	nlm_write_reg(uartbase, offset, value);
}