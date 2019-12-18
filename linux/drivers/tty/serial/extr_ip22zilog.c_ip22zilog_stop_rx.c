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
struct zilog_channel {int dummy; } ;
struct uart_port {int dummy; } ;
struct uart_ip22zilog_port {int /*<<< orphan*/ * curregs; } ;

/* Variables and functions */
 size_t R1 ; 
 int /*<<< orphan*/  RxINT_MASK ; 
 struct uart_ip22zilog_port* UART_ZILOG (struct uart_port*) ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (struct uart_port*) ; 
 scalar_t__ ZS_IS_CONS (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  ip22zilog_maybe_update_regs (struct uart_ip22zilog_port*,struct zilog_channel*) ; 

__attribute__((used)) static void ip22zilog_stop_rx(struct uart_port *port)
{
	struct uart_ip22zilog_port *up = UART_ZILOG(port);
	struct zilog_channel *channel;

	if (ZS_IS_CONS(up))
		return;

	channel = ZILOG_CHANNEL_FROM_PORT(port);

	/* Disable all RX interrupts.  */
	up->curregs[R1] &= ~RxINT_MASK;
	ip22zilog_maybe_update_regs(up, channel);
}