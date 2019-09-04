#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thin_c {TYPE_4__* origin_dev; scalar_t__ dev_id; TYPE_2__* pool_dev; TYPE_5__* pool; int /*<<< orphan*/  td; } ;
struct dm_target {struct thin_c* private; } ;
typedef  int status_type_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int dm_block_t ;
struct TYPE_10__ {int sectors_per_block; } ;
struct TYPE_9__ {TYPE_3__* bdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_7__ {TYPE_1__* bdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DMERR (char*,int) ; 
 scalar_t__ PM_FAIL ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int dm_thin_get_highest_mapped_block (int /*<<< orphan*/ ,int*) ; 
 int dm_thin_get_mapped_count (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  format_dev_t (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_pool_mode (TYPE_5__*) ; 

__attribute__((used)) static void thin_status(struct dm_target *ti, status_type_t type,
			unsigned status_flags, char *result, unsigned maxlen)
{
	int r;
	ssize_t sz = 0;
	dm_block_t mapped, highest;
	char buf[BDEVNAME_SIZE];
	struct thin_c *tc = ti->private;

	if (get_pool_mode(tc->pool) == PM_FAIL) {
		DMEMIT("Fail");
		return;
	}

	if (!tc->td)
		DMEMIT("-");
	else {
		switch (type) {
		case STATUSTYPE_INFO:
			r = dm_thin_get_mapped_count(tc->td, &mapped);
			if (r) {
				DMERR("dm_thin_get_mapped_count returned %d", r);
				goto err;
			}

			r = dm_thin_get_highest_mapped_block(tc->td, &highest);
			if (r < 0) {
				DMERR("dm_thin_get_highest_mapped_block returned %d", r);
				goto err;
			}

			DMEMIT("%llu ", mapped * tc->pool->sectors_per_block);
			if (r)
				DMEMIT("%llu", ((highest + 1) *
						tc->pool->sectors_per_block) - 1);
			else
				DMEMIT("-");
			break;

		case STATUSTYPE_TABLE:
			DMEMIT("%s %lu",
			       format_dev_t(buf, tc->pool_dev->bdev->bd_dev),
			       (unsigned long) tc->dev_id);
			if (tc->origin_dev)
				DMEMIT(" %s", format_dev_t(buf, tc->origin_dev->bdev->bd_dev));
			break;
		}
	}

	return;

err:
	DMEMIT("Error");
}