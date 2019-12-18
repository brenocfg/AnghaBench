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
struct cache {int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char const*,char const*) ; 
 int NOT_CORE_OPTION ; 
 int policy_set_config_value (int /*<<< orphan*/ ,char const*,char const*) ; 
 int process_config_option (struct cache*,char const*,char const*) ; 

__attribute__((used)) static int set_config_value(struct cache *cache, const char *key, const char *value)
{
	int r = process_config_option(cache, key, value);

	if (r == NOT_CORE_OPTION)
		r = policy_set_config_value(cache->policy, key, value);

	if (r)
		DMWARN("bad config value for %s: %s", key, value);

	return r;
}