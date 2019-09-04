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
struct dm_writecache {size_t n_blocks; int /*<<< orphan*/ * entries; int /*<<< orphan*/  block_size; int /*<<< orphan*/  memory_map_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  seq_count; int /*<<< orphan*/  n_blocks; int /*<<< orphan*/  block_size; int /*<<< orphan*/  version; int /*<<< orphan*/ * padding; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMORY_SUPERBLOCK_MAGIC ; 
 int /*<<< orphan*/  MEMORY_SUPERBLOCK_VERSION ; 
 int calculate_memory_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (size_t) ; 
 int /*<<< orphan*/  pmem_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sb (struct dm_writecache*) ; 
 int /*<<< orphan*/  write_original_sector_seq_count (struct dm_writecache*,int /*<<< orphan*/ *,int,int) ; 
 int writecache_alloc_entries (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_commit_flushed (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_flush_all_metadata (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_flush_region (struct dm_writecache*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int init_memory(struct dm_writecache *wc)
{
	size_t b;
	int r;

	r = calculate_memory_size(wc->memory_map_size, wc->block_size, &wc->n_blocks, NULL);
	if (r)
		return r;

	r = writecache_alloc_entries(wc);
	if (r)
		return r;

	for (b = 0; b < ARRAY_SIZE(sb(wc)->padding); b++)
		pmem_assign(sb(wc)->padding[b], cpu_to_le64(0));
	pmem_assign(sb(wc)->version, cpu_to_le32(MEMORY_SUPERBLOCK_VERSION));
	pmem_assign(sb(wc)->block_size, cpu_to_le32(wc->block_size));
	pmem_assign(sb(wc)->n_blocks, cpu_to_le64(wc->n_blocks));
	pmem_assign(sb(wc)->seq_count, cpu_to_le64(0));

	for (b = 0; b < wc->n_blocks; b++)
		write_original_sector_seq_count(wc, &wc->entries[b], -1, -1);

	writecache_flush_all_metadata(wc);
	writecache_commit_flushed(wc);
	pmem_assign(sb(wc)->magic, cpu_to_le32(MEMORY_SUPERBLOCK_MAGIC));
	writecache_flush_region(wc, &sb(wc)->magic, sizeof sb(wc)->magic);
	writecache_commit_flushed(wc);

	return 0;
}