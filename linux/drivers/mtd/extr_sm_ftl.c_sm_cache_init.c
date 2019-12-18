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
struct sm_ftl {int cache_data_invalid_bitmap; int cache_clean; int cache_zone; int cache_block; } ;

/* Variables and functions */

__attribute__((used)) static void sm_cache_init(struct sm_ftl *ftl)
{
	ftl->cache_data_invalid_bitmap = 0xFFFFFFFF;
	ftl->cache_clean = 1;
	ftl->cache_zone = -1;
	ftl->cache_block = -1;
	/*memset(ftl->cache_data, 0xAA, ftl->block_size);*/
}