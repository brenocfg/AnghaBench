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
struct cache {int sectors_per_block; scalar_t__ migration_threshold; int /*<<< orphan*/  nr_io_migrations; int /*<<< orphan*/  tracker; } ;
typedef  scalar_t__ sector_t ;
typedef  enum busy { ____Placeholder_busy } busy ;

/* Variables and functions */
 int BUSY ; 
 int /*<<< orphan*/  HZ ; 
 int IDLE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int iot_idle_for (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum busy spare_migration_bandwidth(struct cache *cache)
{
	bool idle = iot_idle_for(&cache->tracker, HZ);
	sector_t current_volume = (atomic_read(&cache->nr_io_migrations) + 1) *
		cache->sectors_per_block;

	if (idle && current_volume <= cache->migration_threshold)
		return IDLE;
	else
		return BUSY;
}