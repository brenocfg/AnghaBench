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
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static unsigned int mem16_serial_in(struct uart_port *p, int offset)
{
	offset = offset << p->regshift;
	return readw(p->membase + offset);
}