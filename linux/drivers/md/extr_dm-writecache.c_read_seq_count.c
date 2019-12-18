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
struct wc_entry {int /*<<< orphan*/  seq_count; } ;
struct dm_writecache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* memory_entry (struct dm_writecache*,struct wc_entry*) ; 

__attribute__((used)) static uint64_t read_seq_count(struct dm_writecache *wc, struct wc_entry *e)
{
#ifdef DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	return e->seq_count;
#else
	return le64_to_cpu(memory_entry(wc, e)->seq_count);
#endif
}