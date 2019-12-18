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
struct dm_cache_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char const*) ; 
 int EINVAL ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int mq_set_config_value(struct dm_cache_policy *p,
			       const char *key, const char *value)
{
	unsigned long tmp;

	if (kstrtoul(value, 10, &tmp))
		return -EINVAL;

	if (!strcasecmp(key, "random_threshold") ||
	    !strcasecmp(key, "sequential_threshold") ||
	    !strcasecmp(key, "discard_promote_adjustment") ||
	    !strcasecmp(key, "read_promote_adjustment") ||
	    !strcasecmp(key, "write_promote_adjustment")) {
		DMWARN("tunable '%s' no longer has any effect, mq policy is now an alias for smq", key);
		return 0;
	}

	return -EINVAL;
}