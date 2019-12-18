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
struct tty_bufhead {int /*<<< orphan*/  mem_limit; int /*<<< orphan*/  work; int /*<<< orphan*/  priority; int /*<<< orphan*/  mem_used; int /*<<< orphan*/  free; int /*<<< orphan*/  sentinel; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  lock; } ;
struct tty_port {struct tty_bufhead buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTYB_DEFAULT_MEM_LIMIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_to_ldisc ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_buffer_init(struct tty_port *port)
{
	struct tty_bufhead *buf = &port->buf;

	mutex_init(&buf->lock);
	tty_buffer_reset(&buf->sentinel, 0);
	buf->head = &buf->sentinel;
	buf->tail = &buf->sentinel;
	init_llist_head(&buf->free);
	atomic_set(&buf->mem_used, 0);
	atomic_set(&buf->priority, 0);
	INIT_WORK(&buf->work, flush_to_ldisc);
	buf->mem_limit = TTYB_DEFAULT_MEM_LIMIT;
}