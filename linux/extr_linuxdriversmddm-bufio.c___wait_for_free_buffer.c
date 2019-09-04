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
struct dm_bufio_client {int /*<<< orphan*/  free_buffer_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void __wait_for_free_buffer(struct dm_bufio_client *c)
{
	DECLARE_WAITQUEUE(wait, current);

	add_wait_queue(&c->free_buffer_wait, &wait);
	set_current_state(TASK_UNINTERRUPTIBLE);
	dm_bufio_unlock(c);

	io_schedule();

	remove_wait_queue(&c->free_buffer_wait, &wait);

	dm_bufio_lock(c);
}