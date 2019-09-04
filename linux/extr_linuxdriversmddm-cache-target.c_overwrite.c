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
struct per_bio_data {int /*<<< orphan*/  hook_info; } ;
struct dm_cache_migration {int /*<<< orphan*/  cache; int /*<<< orphan*/  k; TYPE_1__* op; struct bio* overwrite_bio; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {scalar_t__ op; int /*<<< orphan*/  cblock; } ;

/* Variables and functions */
 scalar_t__ POLICY_PROMOTE ; 
 int /*<<< orphan*/  accounted_request (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  dm_hook_bio (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ,struct dm_cache_migration*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  init_continuation (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  overwrite_endio ; 
 int /*<<< orphan*/  remap_to_cache (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static void overwrite(struct dm_cache_migration *mg,
		      void (*continuation)(struct work_struct *))
{
	struct bio *bio = mg->overwrite_bio;
	struct per_bio_data *pb = get_per_bio_data(bio);

	dm_hook_bio(&pb->hook_info, bio, overwrite_endio, mg);

	/*
	 * The overwrite bio is part of the copy operation, as such it does
	 * not set/clear discard or dirty flags.
	 */
	if (mg->op->op == POLICY_PROMOTE)
		remap_to_cache(mg->cache, bio, mg->op->cblock);
	else
		remap_to_origin(mg->cache, bio);

	init_continuation(&mg->k, continuation);
	accounted_request(mg->cache, bio);
}