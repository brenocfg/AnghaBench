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
struct dm_bufio_client {int /*<<< orphan*/  free_buffer_wait; int /*<<< orphan*/  need_reserved_buffers; int /*<<< orphan*/  reserved_buffers; } ;
struct dm_buffer {int /*<<< orphan*/  lru_list; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buffer (struct dm_buffer*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __free_buffer_wake(struct dm_buffer *b)
{
	struct dm_bufio_client *c = b->c;

	if (!c->need_reserved_buffers)
		free_buffer(b);
	else {
		list_add(&b->lru_list, &c->reserved_buffers);
		c->need_reserved_buffers--;
	}

	wake_up(&c->free_buffer_wait);
}