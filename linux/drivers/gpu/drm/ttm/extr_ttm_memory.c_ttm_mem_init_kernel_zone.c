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
typedef  int uint64_t ;
struct ttm_mem_zone {char* name; int zone_mem; int max_mem; int emer_mem; int swap_limit; int /*<<< orphan*/  kobj; struct ttm_mem_global* glob; scalar_t__ used_mem; } ;
struct ttm_mem_global {int /*<<< orphan*/  num_zones; struct ttm_mem_zone** zones; int /*<<< orphan*/  kobj; struct ttm_mem_zone* zone_kernel; } ;
struct sysinfo {int totalram; int totalhigh; int mem_unit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct ttm_mem_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_mem_zone_kobj_type ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_mem_init_kernel_zone(struct ttm_mem_global *glob,
				    const struct sysinfo *si)
{
	struct ttm_mem_zone *zone = kzalloc(sizeof(*zone), GFP_KERNEL);
	uint64_t mem;
	int ret;

	if (unlikely(!zone))
		return -ENOMEM;

	mem = si->totalram - si->totalhigh;
	mem *= si->mem_unit;

	zone->name = "kernel";
	zone->zone_mem = mem;
	zone->max_mem = mem >> 1;
	zone->emer_mem = (mem >> 1) + (mem >> 2);
	zone->swap_limit = zone->max_mem - (mem >> 3);
	zone->used_mem = 0;
	zone->glob = glob;
	glob->zone_kernel = zone;
	ret = kobject_init_and_add(
		&zone->kobj, &ttm_mem_zone_kobj_type, &glob->kobj, zone->name);
	if (unlikely(ret != 0)) {
		kobject_put(&zone->kobj);
		return ret;
	}
	glob->zones[glob->num_zones++] = zone;
	return 0;
}