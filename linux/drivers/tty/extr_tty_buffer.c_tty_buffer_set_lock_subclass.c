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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct tty_port {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LOCK_SLAVE ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_buffer_set_lock_subclass(struct tty_port *port)
{
	lockdep_set_subclass(&port->buf.lock, TTY_LOCK_SLAVE);
}