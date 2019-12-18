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
struct uart_port {int uartclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DREG ; 
 int /*<<< orphan*/  UART_MNDREG ; 
 int /*<<< orphan*/  UART_MREG ; 
 int /*<<< orphan*/  UART_NREG ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_serial_set_mnd_regs_tcxo(struct uart_port *port)
{
	msm_write(port, 0x06, UART_MREG);
	msm_write(port, 0xF1, UART_NREG);
	msm_write(port, 0x0F, UART_DREG);
	msm_write(port, 0x1A, UART_MNDREG);
	port->uartclk = 1843200;
}