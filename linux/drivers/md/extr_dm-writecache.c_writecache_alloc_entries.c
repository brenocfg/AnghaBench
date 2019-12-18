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
struct wc_entry {size_t index; int write_in_progress; } ;
struct dm_writecache {size_t n_blocks; struct wc_entry* entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (int,size_t) ; 
 struct wc_entry* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int writecache_alloc_entries(struct dm_writecache *wc)
{
	size_t b;

	if (wc->entries)
		return 0;
	wc->entries = vmalloc(array_size(sizeof(struct wc_entry), wc->n_blocks));
	if (!wc->entries)
		return -ENOMEM;
	for (b = 0; b < wc->n_blocks; b++) {
		struct wc_entry *e = &wc->entries[b];
		e->index = b;
		e->write_in_progress = false;
	}

	return 0;
}