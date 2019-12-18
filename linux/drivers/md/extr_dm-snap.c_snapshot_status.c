#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {unsigned int discard_zeroes_cow; unsigned int discard_passdown_origin; TYPE_4__* store; TYPE_2__* cow; TYPE_1__* origin; int /*<<< orphan*/  lock; int /*<<< orphan*/  snapshot_overflowed; int /*<<< orphan*/  merge_failed; int /*<<< orphan*/  valid; } ;
typedef  int status_type_t ;
typedef  scalar_t__ sector_t ;
struct TYPE_9__ {TYPE_3__* type; } ;
struct TYPE_8__ {unsigned int (* status ) (TYPE_4__*,int,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* usage ) (TYPE_4__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 unsigned int stub2 (TYPE_4__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snapshot_status(struct dm_target *ti, status_type_t type,
			    unsigned status_flags, char *result, unsigned maxlen)
{
	unsigned sz = 0;
	struct dm_snapshot *snap = ti->private;
	unsigned num_features;

	switch (type) {
	case STATUSTYPE_INFO:

		down_write(&snap->lock);

		if (!snap->valid)
			DMEMIT("Invalid");
		else if (snap->merge_failed)
			DMEMIT("Merge failed");
		else if (snap->snapshot_overflowed)
			DMEMIT("Overflow");
		else {
			if (snap->store->type->usage) {
				sector_t total_sectors, sectors_allocated,
					 metadata_sectors;
				snap->store->type->usage(snap->store,
							 &total_sectors,
							 &sectors_allocated,
							 &metadata_sectors);
				DMEMIT("%llu/%llu %llu",
				       (unsigned long long)sectors_allocated,
				       (unsigned long long)total_sectors,
				       (unsigned long long)metadata_sectors);
			}
			else
				DMEMIT("Unknown");
		}

		up_write(&snap->lock);

		break;

	case STATUSTYPE_TABLE:
		/*
		 * kdevname returns a static pointer so we need
		 * to make private copies if the output is to
		 * make sense.
		 */
		DMEMIT("%s %s", snap->origin->name, snap->cow->name);
		sz += snap->store->type->status(snap->store, type, result + sz,
						maxlen - sz);
		num_features = snap->discard_zeroes_cow + snap->discard_passdown_origin;
		if (num_features) {
			DMEMIT(" %u", num_features);
			if (snap->discard_zeroes_cow)
				DMEMIT(" discard_zeroes_cow");
			if (snap->discard_passdown_origin)
				DMEMIT(" discard_passdown_origin");
		}
		break;
	}
}