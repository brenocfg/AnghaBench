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
struct wc_entry {int seq_count; } ;
struct dm_writecache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 TYPE_1__* memory_entry (struct dm_writecache*,struct wc_entry*) ; 
 int /*<<< orphan*/  pmem_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_seq_count(struct dm_writecache *wc, struct wc_entry *e)
{
#ifdef DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	e->seq_count = -1;
#endif
	pmem_assign(memory_entry(wc, e)->seq_count, cpu_to_le64(-1));
}