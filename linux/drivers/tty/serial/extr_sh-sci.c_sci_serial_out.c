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
struct plat_sci_reg {int size; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 struct plat_sci_reg* sci_getreg (struct uart_port*,int) ; 

__attribute__((used)) static void sci_serial_out(struct uart_port *p, int offset, int value)
{
	const struct plat_sci_reg *reg = sci_getreg(p, offset);

	if (reg->size == 8)
		iowrite8(value, p->membase + (reg->offset << p->regshift));
	else if (reg->size == 16)
		iowrite16(value, p->membase + (reg->offset << p->regshift));
	else
		WARN(1, "Invalid register access\n");
}