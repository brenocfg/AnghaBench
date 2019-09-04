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
struct dm_cache_policy_type {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dm_cache_policy_type* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dm_cache_policy_type* __find_policy (char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_cache_policy_type *__get_policy_once(const char *name)
{
	struct dm_cache_policy_type *t = __find_policy(name);

	if (t && !try_module_get(t->owner)) {
		DMWARN("couldn't get module %s", name);
		t = ERR_PTR(-EINVAL);
	}

	return t;
}