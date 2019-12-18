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
struct wc_memory_superblock {int dummy; } ;
struct dm_writecache {struct wc_memory_superblock* memory_map; } ;

/* Variables and functions */

__attribute__((used)) static struct wc_memory_superblock *sb(struct dm_writecache *wc)
{
	return wc->memory_map;
}