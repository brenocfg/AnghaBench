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
struct cache {int dummy; } ;

/* Variables and functions */
 struct cache* cache_chain_instantiate (unsigned int) ; 
 int /*<<< orphan*/  cacheinfo_sysfs_populate (unsigned int,struct cache*) ; 

void cacheinfo_cpu_online(unsigned int cpu_id)
{
	struct cache *cache;

	cache = cache_chain_instantiate(cpu_id);
	if (!cache)
		return;

	cacheinfo_sysfs_populate(cpu_id, cache);
}