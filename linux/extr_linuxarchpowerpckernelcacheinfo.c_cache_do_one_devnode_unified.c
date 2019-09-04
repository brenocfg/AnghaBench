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
 int /*<<< orphan*/  cache_is_unified_d (struct device_node*) ; 
 struct cache* new_cache (int /*<<< orphan*/ ,int,struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct device_node*) ; 

__attribute__((used)) static struct cache *cache_do_one_devnode_unified(struct device_node *node, int level)
{
	pr_debug("creating L%d ucache for %pOF\n", level, node);

	return new_cache(cache_is_unified_d(node), level, node);
}