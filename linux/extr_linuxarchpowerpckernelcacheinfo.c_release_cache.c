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
struct cache {int /*<<< orphan*/  ofnode; int /*<<< orphan*/  list; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_type_string (struct cache*) ; 
 int /*<<< orphan*/  kfree (struct cache*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_cache_debugcheck (struct cache*) ; 

__attribute__((used)) static void release_cache(struct cache *cache)
{
	if (!cache)
		return;

	pr_debug("freeing L%d %s cache for %pOF\n", cache->level,
		 cache_type_string(cache), cache->ofnode);

	release_cache_debugcheck(cache);
	list_del(&cache->list);
	of_node_put(cache->ofnode);
	kfree(cache);
}