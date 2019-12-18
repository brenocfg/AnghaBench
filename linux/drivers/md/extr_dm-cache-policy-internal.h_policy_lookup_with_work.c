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
struct policy_work {int dummy; } ;
struct dm_cache_policy {int (* lookup_with_work ) (struct dm_cache_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct policy_work**) ;int (* lookup ) (struct dm_cache_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int stub1 (struct dm_cache_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int stub2 (struct dm_cache_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct policy_work**) ; 

__attribute__((used)) static inline int policy_lookup_with_work(struct dm_cache_policy *p,
					  dm_oblock_t oblock, dm_cblock_t *cblock,
					  int data_dir, bool fast_copy,
					  struct policy_work **work)
{
	if (!p->lookup_with_work) {
		*work = NULL;
		return p->lookup(p, oblock, cblock, data_dir, fast_copy, NULL);
	}

	return p->lookup_with_work(p, oblock, cblock, data_dir, fast_copy, work);
}