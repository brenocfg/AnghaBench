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
typedef  int u8 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static void lpuart_wait_bit_set(struct uart_port *port, unsigned int offset,
				u8 bit)
{
	while (!(readb(port->membase + offset) & bit))
		cpu_relax();
}