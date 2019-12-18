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
struct wc_memory_entry {int dummy; } ;
struct wc_entry {int dummy; } ;
struct dm_writecache {int /*<<< orphan*/  freelist_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_seq_count (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  memory_entry (struct dm_writecache*,struct wc_entry*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writecache_add_to_freelist (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  writecache_flush_region (struct dm_writecache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writecache_unlink (struct dm_writecache*,struct wc_entry*) ; 

__attribute__((used)) static void writecache_free_entry(struct dm_writecache *wc, struct wc_entry *e)
{
	writecache_unlink(wc, e);
	writecache_add_to_freelist(wc, e);
	clear_seq_count(wc, e);
	writecache_flush_region(wc, memory_entry(wc, e), sizeof(struct wc_memory_entry));
	if (unlikely(waitqueue_active(&wc->freelist_wait)))
		wake_up(&wc->freelist_wait);
}