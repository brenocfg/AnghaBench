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
struct kobject {int dummy; } ;
struct cache_index_dir {struct cache* cache; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 struct cache_index_dir* kobj_to_cache_index_dir (struct kobject*) ; 

__attribute__((used)) static struct cache *index_kobj_to_cache(struct kobject *k)
{
	struct cache_index_dir *index;

	index = kobj_to_cache_index_dir(k);

	return index->cache;
}