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
typedef  unsigned long u64 ;
typedef  size_t u32 ;
struct arena_info {unsigned long sector_size; int /*<<< orphan*/  err_lock; TYPE_1__* freelist; } ;
struct TYPE_2__ {size_t block; scalar_t__ has_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int arena_write_bytes (struct arena_info*,unsigned long,void*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 unsigned long to_namespace_offset (struct arena_info*,size_t) ; 

__attribute__((used)) static int arena_clear_freelist_error(struct arena_info *arena, u32 lane)
{
	int ret = 0;

	if (arena->freelist[lane].has_err) {
		void *zero_page = page_address(ZERO_PAGE(0));
		u32 lba = arena->freelist[lane].block;
		u64 nsoff = to_namespace_offset(arena, lba);
		unsigned long len = arena->sector_size;

		mutex_lock(&arena->err_lock);

		while (len) {
			unsigned long chunk = min(len, PAGE_SIZE);

			ret = arena_write_bytes(arena, nsoff, zero_page,
				chunk, 0);
			if (ret)
				break;
			len -= chunk;
			nsoff += chunk;
			if (len == 0)
				arena->freelist[lane].has_err = 0;
		}
		mutex_unlock(&arena->err_lock);
	}
	return ret;
}