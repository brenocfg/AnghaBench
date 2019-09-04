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
struct tty_struct {struct serial_state* driver_data; } ;
struct serial_state {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  rs_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_hangup(struct tty_struct *tty)
{
	struct serial_state *info = tty->driver_data;

	rs_flush_buffer(tty);
	tty_port_hangup(&info->port);
}