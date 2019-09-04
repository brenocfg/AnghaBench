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
struct device_node {int dummy; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int) ; 
 int /*<<< orphan*/  cache_cpu_set (struct cache*,unsigned int) ; 
 struct cache* cache_lookup_or_instantiate (struct device_node*,int) ; 
 int /*<<< orphan*/  do_subsidiary_caches (struct cache*) ; 
 struct device_node* of_get_cpu_node (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static struct cache *cache_chain_instantiate(unsigned int cpu_id)
{
	struct device_node *cpu_node;
	struct cache *cpu_cache = NULL;

	pr_debug("creating cache object(s) for CPU %i\n", cpu_id);

	cpu_node = of_get_cpu_node(cpu_id, NULL);
	WARN_ONCE(!cpu_node, "no OF node found for CPU %i\n", cpu_id);
	if (!cpu_node)
		goto out;

	cpu_cache = cache_lookup_or_instantiate(cpu_node, 1);
	if (!cpu_cache)
		goto out;

	do_subsidiary_caches(cpu_cache);

	cache_cpu_set(cpu_cache, cpu_id);
out:
	of_node_put(cpu_node);

	return cpu_cache;
}