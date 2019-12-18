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
struct tty_struct {int dummy; } ;
struct tty_port {int dummy; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct tegra_uart_port {TYPE_2__ uport; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_uart_handle_rx_pio (struct tegra_uart_port*,struct tty_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 

__attribute__((used)) static void do_handle_rx_pio(struct tegra_uart_port *tup)
{
	struct tty_struct *tty = tty_port_tty_get(&tup->uport.state->port);
	struct tty_port *port = &tup->uport.state->port;

	tegra_uart_handle_rx_pio(tup, port);
	if (tty) {
		tty_flip_buffer_push(port);
		tty_kref_put(tty);
	}
}