#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct exar8250 {scalar_t__ virt; TYPE_1__* board; } ;
struct TYPE_2__ {int num_ports; } ;

/* Variables and functions */
 scalar_t__ UART_EXAR_INT0 ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static inline void exar_misc_clear(struct exar8250 *priv)
{
	/* Clear all PCI interrupts by reading INT0. No effect on IIR */
	readb(priv->virt + UART_EXAR_INT0);

	/* Clear INT0 for Expansion Interface slave ports, too */
	if (priv->board->num_ports > 8)
		readb(priv->virt + 0x2000 + UART_EXAR_INT0);
}