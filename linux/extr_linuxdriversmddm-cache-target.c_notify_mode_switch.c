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
typedef  enum cache_metadata_mode { ____Placeholder_cache_metadata_mode } cache_metadata_mode ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMINFO (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void notify_mode_switch(struct cache *cache, enum cache_metadata_mode mode)
{
	const char *descs[] = {
		"write",
		"read-only",
		"fail"
	};

	dm_table_event(cache->ti->table);
	DMINFO("%s: switching cache to %s mode",
	       cache_device_name(cache), descs[(int)mode]);
}