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
struct dm_bufio_client {int dummy; } ;
struct dm_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  hold_count; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct dm_buffer* __find (struct dm_bufio_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_buffer_wake (struct dm_buffer*) ; 
 int /*<<< orphan*/  __unlink_buffer (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 scalar_t__ likely (int) ; 

void dm_bufio_forget(struct dm_bufio_client *c, sector_t block)
{
	struct dm_buffer *b;

	dm_bufio_lock(c);

	b = __find(c, block);
	if (b && likely(!b->hold_count) && likely(!b->state)) {
		__unlink_buffer(b);
		__free_buffer_wake(b);
	}

	dm_bufio_unlock(c);
}