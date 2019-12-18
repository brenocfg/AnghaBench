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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ SE_UART_MANUAL_RFR ; 
 unsigned int TIOCM_RTS ; 
 int UART_MANUAL_RFR_EN ; 
 int UART_RFR_NOT_READY ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_set_mctrl(struct uart_port *uport,
							unsigned int mctrl)
{
	u32 uart_manual_rfr = 0;

	if (uart_console(uport))
		return;

	if (!(mctrl & TIOCM_RTS))
		uart_manual_rfr = UART_MANUAL_RFR_EN | UART_RFR_NOT_READY;
	writel(uart_manual_rfr, uport->membase + SE_UART_MANUAL_RFR);
}