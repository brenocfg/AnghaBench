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
struct cache {unsigned long migration_threshold; } ;

/* Variables and functions */
 int EINVAL ; 
 int NOT_CORE_OPTION ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int process_config_option(struct cache *cache, const char *key, const char *value)
{
	unsigned long tmp;

	if (!strcasecmp(key, "migration_threshold")) {
		if (kstrtoul(value, 10, &tmp))
			return -EINVAL;

		cache->migration_threshold = tmp;
		return 0;
	}

	return NOT_CORE_OPTION;
}