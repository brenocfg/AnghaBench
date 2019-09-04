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
struct writeback_struct {int /*<<< orphan*/  bio; struct dm_writecache* wc; } ;
struct wc_entry {int dummy; } ;
struct dm_writecache {unsigned int block_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ bio_add_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 void* memory_data (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  persistent_memory_flush_cache (void*,unsigned int) ; 
 int /*<<< orphan*/  persistent_memory_page (void*) ; 
 int /*<<< orphan*/  persistent_memory_page_offset (void*) ; 

__attribute__((used)) static bool wc_add_block(struct writeback_struct *wb, struct wc_entry *e, gfp_t gfp)
{
	struct dm_writecache *wc = wb->wc;
	unsigned block_size = wc->block_size;
	void *address = memory_data(wc, e);

	persistent_memory_flush_cache(address, block_size);
	return bio_add_page(&wb->bio, persistent_memory_page(address),
			    block_size, persistent_memory_page_offset(address)) != 0;
}