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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DLL_EM ; 
 int /*<<< orphan*/  UART_DLM_EM ; 
 int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial8250_em_serial_dl_read(struct uart_8250_port *up)
{
	return serial_in(up, UART_DLL_EM) | serial_in(up, UART_DLM_EM) << 8;
}