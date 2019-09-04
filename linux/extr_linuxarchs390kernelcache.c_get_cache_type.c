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
struct cache_info {scalar_t__ scope; size_t type; } ;
typedef  enum cache_type { ____Placeholder_cache_type } cache_type ;

/* Variables and functions */
 int CACHE_MAX_LEVEL ; 
 scalar_t__ CACHE_SCOPE_PRIVATE ; 
 scalar_t__ CACHE_SCOPE_SHARED ; 
 int CACHE_TYPE_NOCACHE ; 
 int* cache_type_map ; 

__attribute__((used)) static inline enum cache_type get_cache_type(struct cache_info *ci, int level)
{
	if (level >= CACHE_MAX_LEVEL)
		return CACHE_TYPE_NOCACHE;
	ci += level;
	if (ci->scope != CACHE_SCOPE_SHARED && ci->scope != CACHE_SCOPE_PRIVATE)
		return CACHE_TYPE_NOCACHE;
	return cache_type_map[ci->type];
}