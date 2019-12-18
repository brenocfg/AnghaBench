#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mirror_set {int /*<<< orphan*/  rh; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_3__ {scalar_t__ (* in_sync ) (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ choose_mirror (struct mirror_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (int /*<<< orphan*/ ,struct bio*) ; 
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mirror_available(struct mirror_set *ms, struct bio *bio)
{
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	region_t region = dm_rh_bio_to_region(ms->rh, bio);

	if (log->type->in_sync(log, region, 0))
		return choose_mirror(ms,  bio->bi_iter.bi_sector) ? 1 : 0;

	return 0;
}