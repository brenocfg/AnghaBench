#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* state; } ;
struct uart_8250_port {TYPE_2__ port; } ;
struct timer_list {int dummy; } ;
struct aspeed_vuart {int /*<<< orphan*/  unthrottle_timer; struct uart_8250_port* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_vuart_unthrottle (TYPE_2__*) ; 
 struct aspeed_vuart* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tty_buffer_space_avail (int /*<<< orphan*/ *) ; 
 scalar_t__ unthrottle_timeout ; 
 int /*<<< orphan*/  unthrottle_timer ; 
 struct aspeed_vuart* vuart ; 

__attribute__((used)) static void aspeed_vuart_unthrottle_exp(struct timer_list *timer)
{
	struct aspeed_vuart *vuart = from_timer(vuart, timer, unthrottle_timer);
	struct uart_8250_port *up = vuart->port;

	if (!tty_buffer_space_avail(&up->port.state->port)) {
		mod_timer(&vuart->unthrottle_timer,
			  jiffies + unthrottle_timeout);
		return;
	}

	aspeed_vuart_unthrottle(&up->port);
}