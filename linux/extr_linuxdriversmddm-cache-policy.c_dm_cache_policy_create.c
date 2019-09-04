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
struct dm_cache_policy_type {struct dm_cache_policy* (* create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dm_cache_policy {struct dm_cache_policy_type* private; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dm_cache_policy* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dm_cache_policy_type* get_policy (char const*) ; 
 int /*<<< orphan*/  put_policy (struct dm_cache_policy_type*) ; 
 struct dm_cache_policy* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dm_cache_policy *dm_cache_policy_create(const char *name,
					       dm_cblock_t cache_size,
					       sector_t origin_size,
					       sector_t cache_block_size)
{
	struct dm_cache_policy *p = NULL;
	struct dm_cache_policy_type *type;

	type = get_policy(name);
	if (!type) {
		DMWARN("unknown policy type");
		return ERR_PTR(-EINVAL);
	}

	p = type->create(cache_size, origin_size, cache_block_size);
	if (!p) {
		put_policy(type);
		return ERR_PTR(-ENOMEM);
	}
	p->private = type;

	return p;
}