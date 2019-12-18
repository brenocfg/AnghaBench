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
struct uart_amba_port {int /*<<< orphan*/  im; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IMSC ; 
 int /*<<< orphan*/  UART011_TXIM ; 
 scalar_t__ pl011_tx_chars (struct uart_amba_port*,int) ; 
 int /*<<< orphan*/  pl011_write (int /*<<< orphan*/ ,struct uart_amba_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pl011_start_tx_pio(struct uart_amba_port *uap)
{
	if (pl011_tx_chars(uap, false)) {
		uap->im |= UART011_TXIM;
		pl011_write(uap->im, uap, REG_IMSC);
	}
}