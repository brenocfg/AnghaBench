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
struct dm_writecache {scalar_t__ writeback_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  writecache_wait_on_freelist (struct dm_writecache*) ; 

__attribute__((used)) static bool writecache_wait_for_writeback(struct dm_writecache *wc)
{
	if (wc->writeback_size) {
		writecache_wait_on_freelist(wc);
		return true;
	}
	return false;
}