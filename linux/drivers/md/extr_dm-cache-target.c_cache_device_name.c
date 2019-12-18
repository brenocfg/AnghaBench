#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {TYPE_1__* ti; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 char const* dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *cache_device_name(struct cache *cache)
{
	return dm_device_name(dm_table_get_md(cache->ti->table));
}