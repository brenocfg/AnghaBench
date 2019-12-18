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
struct uart_port {int regshift; scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int dw8250_modify_msr (struct uart_port*,int,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int dw8250_serial_in32(struct uart_port *p, int offset)
{
	unsigned int value = readl(p->membase + (offset << p->regshift));

	return dw8250_modify_msr(p, offset, value);
}