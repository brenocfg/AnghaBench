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
typedef  scalar_t__ u32 ;
struct uart_port {int iotype; scalar_t__ membase; } ;

/* Variables and functions */
#define  UPIO_MEM32 129 
#define  UPIO_MEM32BE 128 
 int /*<<< orphan*/  iowrite32be (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void lpuart32_write(struct uart_port *port, u32 val,
				  u32 off)
{
	switch (port->iotype) {
	case UPIO_MEM32:
		writel(val, port->membase + off);
		break;
	case UPIO_MEM32BE:
		iowrite32be(val, port->membase + off);
		break;
	}
}