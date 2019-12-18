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
struct tty_port {int close_delay; int closing_wait; int /*<<< orphan*/  kref; int /*<<< orphan*/ * client_ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  default_client_ops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tty_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_init (struct tty_port*) ; 

void tty_port_init(struct tty_port *port)
{
	memset(port, 0, sizeof(*port));
	tty_buffer_init(port);
	init_waitqueue_head(&port->open_wait);
	init_waitqueue_head(&port->delta_msr_wait);
	mutex_init(&port->mutex);
	mutex_init(&port->buf_mutex);
	spin_lock_init(&port->lock);
	port->close_delay = (50 * HZ) / 100;
	port->closing_wait = (3000 * HZ) / 100;
	port->client_ops = &default_client_ops;
	kref_init(&port->kref);
}