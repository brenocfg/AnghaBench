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
struct dm_writecache {int /*<<< orphan*/  endio_list_lock; int /*<<< orphan*/  endio_list; int /*<<< orphan*/  endio_thread; } ;
struct copy_struct {int /*<<< orphan*/  endio_entry; int /*<<< orphan*/  error; struct dm_writecache* wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writecache_copy_endio(int read_err, unsigned long write_err, void *ptr)
{
	struct copy_struct *c = ptr;
	struct dm_writecache *wc = c->wc;

	c->error = likely(!(read_err | write_err)) ? 0 : -EIO;

	raw_spin_lock_irq(&wc->endio_list_lock);
	if (unlikely(list_empty(&wc->endio_list)))
		wake_up_process(wc->endio_thread);
	list_add_tail(&c->endio_entry, &wc->endio_list);
	raw_spin_unlock_irq(&wc->endio_list_lock);
}