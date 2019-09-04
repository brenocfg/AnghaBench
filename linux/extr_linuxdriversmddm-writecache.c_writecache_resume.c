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
typedef  int /*<<< orphan*/  uint64_t ;
struct wc_entry {int dummy; } ;
struct dm_writecache {size_t n_blocks; struct wc_entry* entries; int /*<<< orphan*/  seq_count; scalar_t__ freelist_size; int /*<<< orphan*/  freelist; int /*<<< orphan*/ * current_free; void* freetree; int /*<<< orphan*/  lru; void* tree; int /*<<< orphan*/  memory_map_size; int /*<<< orphan*/  memory_map; } ;
struct dm_target {struct dm_writecache* private; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int /*<<< orphan*/  seq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 scalar_t__ WC_MODE_PMEM (struct dm_writecache*) ; 
 scalar_t__ WC_MODE_SORT_FREELIST (struct dm_writecache*) ; 
 int /*<<< orphan*/  clear_seq_count (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int memcpy_mcsafe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  persistent_memory_invalidate_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_original_sector (struct dm_writecache*,struct wc_entry*) ; 
 int read_seq_count (struct dm_writecache*,struct wc_entry*) ; 
 TYPE_1__* sb (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_add_to_freelist (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  writecache_commit_flushed (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_entry_is_committed (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  writecache_error (struct dm_writecache*,int,char*,unsigned long long,...) ; 
 struct wc_entry* writecache_find_entry (struct dm_writecache*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writecache_flush_all_metadata (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_free_entry (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  writecache_insert_entry (struct dm_writecache*,struct wc_entry*) ; 

__attribute__((used)) static void writecache_resume(struct dm_target *ti)
{
	struct dm_writecache *wc = ti->private;
	size_t b;
	bool need_flush = false;
	__le64 sb_seq_count;
	int r;

	wc_lock(wc);

	if (WC_MODE_PMEM(wc))
		persistent_memory_invalidate_cache(wc->memory_map, wc->memory_map_size);

	wc->tree = RB_ROOT;
	INIT_LIST_HEAD(&wc->lru);
	if (WC_MODE_SORT_FREELIST(wc)) {
		wc->freetree = RB_ROOT;
		wc->current_free = NULL;
	} else {
		INIT_LIST_HEAD(&wc->freelist);
	}
	wc->freelist_size = 0;

	r = memcpy_mcsafe(&sb_seq_count, &sb(wc)->seq_count, sizeof(uint64_t));
	if (r) {
		writecache_error(wc, r, "hardware memory error when reading superblock: %d", r);
		sb_seq_count = cpu_to_le64(0);
	}
	wc->seq_count = le64_to_cpu(sb_seq_count);

#ifdef DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	for (b = 0; b < wc->n_blocks; b++) {
		struct wc_entry *e = &wc->entries[b];
		struct wc_memory_entry wme;
		if (writecache_has_error(wc)) {
			e->original_sector = -1;
			e->seq_count = -1;
			continue;
		}
		r = memcpy_mcsafe(&wme, memory_entry(wc, e), sizeof(struct wc_memory_entry));
		if (r) {
			writecache_error(wc, r, "hardware memory error when reading metadata entry %lu: %d",
					 (unsigned long)b, r);
			e->original_sector = -1;
			e->seq_count = -1;
		} else {
			e->original_sector = le64_to_cpu(wme.original_sector);
			e->seq_count = le64_to_cpu(wme.seq_count);
		}
	}
#endif
	for (b = 0; b < wc->n_blocks; b++) {
		struct wc_entry *e = &wc->entries[b];
		if (!writecache_entry_is_committed(wc, e)) {
			if (read_seq_count(wc, e) != -1) {
erase_this:
				clear_seq_count(wc, e);
				need_flush = true;
			}
			writecache_add_to_freelist(wc, e);
		} else {
			struct wc_entry *old;

			old = writecache_find_entry(wc, read_original_sector(wc, e), 0);
			if (!old) {
				writecache_insert_entry(wc, e);
			} else {
				if (read_seq_count(wc, old) == read_seq_count(wc, e)) {
					writecache_error(wc, -EINVAL,
						 "two identical entries, position %llu, sector %llu, sequence %llu",
						 (unsigned long long)b, (unsigned long long)read_original_sector(wc, e),
						 (unsigned long long)read_seq_count(wc, e));
				}
				if (read_seq_count(wc, old) > read_seq_count(wc, e)) {
					goto erase_this;
				} else {
					writecache_free_entry(wc, old);
					writecache_insert_entry(wc, e);
					need_flush = true;
				}
			}
		}
		cond_resched();
	}

	if (need_flush) {
		writecache_flush_all_metadata(wc);
		writecache_commit_flushed(wc);
	}

	wc_unlock(wc);
}