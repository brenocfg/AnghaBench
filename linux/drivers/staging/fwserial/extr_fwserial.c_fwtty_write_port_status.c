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
struct fwtty_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_write_port_status(struct fwtty_port *port)
{
	int err;

	spin_lock_bh(&port->lock);
	err = __fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);
	return err;
}