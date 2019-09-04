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
struct cache {int /*<<< orphan*/  sectors_per_block; int /*<<< orphan*/  cache_dev; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_dev_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_cblock_t get_cache_dev_size(struct cache *cache)
{
	sector_t size = get_dev_size(cache->cache_dev);
	(void) sector_div(size, cache->sectors_per_block);
	return to_cblock(size);
}