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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  throttled; } ;
struct fwtty_port {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static void fwtty_throttle(struct tty_struct *tty)
{
	struct fwtty_port *port = tty->driver_data;

	/*
	 * Ignore throttling (but not unthrottling).
	 * It only makes sense to throttle when data will no longer be
	 * accepted by the tty flip buffer. For example, it is
	 * possible for received data to overflow the tty buffer long
	 * before the line discipline ever has a chance to throttle the driver.
	 * Additionally, the driver may have already completed the I/O
	 * but the tty buffer is still emptying, so the line discipline is
	 * throttling and unthrottling nothing.
	 */

	++port->stats.throttled;
}