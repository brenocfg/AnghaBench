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
struct tty_bufhead {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  priority; TYPE_1__* head; } ;
struct tty_port {struct tty_bufhead buf; } ;
struct TYPE_2__ {scalar_t__ commit; scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

void tty_buffer_unlock_exclusive(struct tty_port *port)
{
	struct tty_bufhead *buf = &port->buf;
	int restart;

	restart = buf->head->commit != buf->head->read;

	atomic_dec(&buf->priority);
	mutex_unlock(&buf->lock);
	if (restart)
		queue_work(system_unbound_wq, &buf->work);
}