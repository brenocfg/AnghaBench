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
struct dm_writecache {scalar_t__ start_sector; scalar_t__ memory_map; scalar_t__ memory_vmapped; } ;

/* Variables and functions */
 size_t SECTOR_SHIFT ; 
 int /*<<< orphan*/  vunmap (scalar_t__) ; 

__attribute__((used)) static void persistent_memory_release(struct dm_writecache *wc)
{
	if (wc->memory_vmapped)
		vunmap(wc->memory_map - ((size_t)wc->start_sector << SECTOR_SHIFT));
}