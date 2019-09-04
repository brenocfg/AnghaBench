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
struct wc_entry {int dummy; } ;
struct dm_writecache {scalar_t__ seq_count; } ;

/* Variables and functions */
 scalar_t__ read_seq_count (struct dm_writecache*,struct wc_entry*) ; 

__attribute__((used)) static bool writecache_entry_is_committed(struct dm_writecache *wc, struct wc_entry *e)
{
	return read_seq_count(wc, e) < wc->seq_count;
}