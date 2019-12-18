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
#define  UART_FCR 129 
 unsigned int UART_FCR_UME ; 
#define  UART_MCR 128 
 unsigned int UART_MCR_FCM ; 
 unsigned int UART_MCR_MDCE ; 
 unsigned int readb (scalar_t__) ; 

__attribute__((used)) static unsigned int ingenic_uart_serial_in(struct uart_port *p, int offset)
{
	unsigned int value;

	value = readb(p->membase + (offset << p->regshift));

	/* Hide non-16550 compliant bits from higher levels */
	switch (offset) {
	case UART_FCR:
		value &= ~UART_FCR_UME;
		break;

	case UART_MCR:
		value &= ~(UART_MCR_MDCE | UART_MCR_FCM);
		break;

	default:
		break;
	}
	return value;
}