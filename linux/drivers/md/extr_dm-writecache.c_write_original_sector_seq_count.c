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
typedef  void* uint64_t ;
struct wc_memory_entry {void* seq_count; void* original_sector; } ;
struct wc_entry {void* seq_count; void* original_sector; } ;
struct dm_writecache {int dummy; } ;

/* Variables and functions */
 void* cpu_to_le64 (void*) ; 
 int /*<<< orphan*/ * memory_entry (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  pmem_assign (int /*<<< orphan*/ ,struct wc_memory_entry) ; 

__attribute__((used)) static void write_original_sector_seq_count(struct dm_writecache *wc, struct wc_entry *e,
					    uint64_t original_sector, uint64_t seq_count)
{
	struct wc_memory_entry me;
#ifdef DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	e->original_sector = original_sector;
	e->seq_count = seq_count;
#endif
	me.original_sector = cpu_to_le64(original_sector);
	me.seq_count = cpu_to_le64(seq_count);
	pmem_assign(*memory_entry(wc, e), me);
}