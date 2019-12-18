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
struct dm_cache_policy_type {int hint_size; unsigned long long name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,unsigned long long) ; 
 int EINVAL ; 
 scalar_t__ __find_policy (unsigned long long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_list ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dm_cache_policy_register(struct dm_cache_policy_type *type)
{
	int r;

	/* One size fits all for now */
	if (type->hint_size != 0 && type->hint_size != 4) {
		DMWARN("hint size must be 0 or 4 but %llu supplied.", (unsigned long long) type->hint_size);
		return -EINVAL;
	}

	spin_lock(&register_lock);
	if (__find_policy(type->name)) {
		DMWARN("attempt to register policy under duplicate name %s", type->name);
		r = -EINVAL;
	} else {
		list_add(&type->list, &register_list);
		r = 0;
	}
	spin_unlock(&register_lock);

	return r;
}