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
struct cacheinfo {unsigned int level; int type; int physical_line_partition; int attributes; } ;
typedef  enum cache_type { ____Placeholder_cache_type } cache_type ;

/* Variables and functions */
 int CACHE_READ_ALLOCATE ; 
 int CACHE_WRITE_ALLOCATE ; 
 int CACHE_WRITE_BACK ; 

__attribute__((used)) static void ci_leaf_init(struct cacheinfo *this_leaf,
			 struct device_node *node,
			 enum cache_type type, unsigned int level)
{
	this_leaf->level = level;
	this_leaf->type = type;
	/* not a sector cache */
	this_leaf->physical_line_partition = 1;
	/* TODO: Add to DTS */
	this_leaf->attributes =
		CACHE_WRITE_BACK
		| CACHE_READ_ALLOCATE
		| CACHE_WRITE_ALLOCATE;
}