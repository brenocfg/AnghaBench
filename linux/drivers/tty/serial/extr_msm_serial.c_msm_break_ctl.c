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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_CR ; 
 int /*<<< orphan*/  UART_CR_CMD_START_BREAK ; 
 int /*<<< orphan*/  UART_CR_CMD_STOP_BREAK ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_break_ctl(struct uart_port *port, int break_ctl)
{
	if (break_ctl)
		msm_write(port, UART_CR_CMD_START_BREAK, UART_CR);
	else
		msm_write(port, UART_CR_CMD_STOP_BREAK, UART_CR);
}