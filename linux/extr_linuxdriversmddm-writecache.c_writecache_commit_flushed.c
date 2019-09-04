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
struct dm_writecache {int dummy; } ;

/* Variables and functions */
 scalar_t__ WC_MODE_PMEM (struct dm_writecache*) ; 
 int /*<<< orphan*/  ssd_commit_flushed (struct dm_writecache*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void writecache_commit_flushed(struct dm_writecache *wc)
{
	if (WC_MODE_PMEM(wc))
		wmb();
	else
		ssd_commit_flushed(wc);
}