#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {TYPE_3__* queue; int /*<<< orphan*/  flags; } ;
struct dm_table {int dummy; } ;
struct TYPE_6__ {TYPE_2__* backing_dev_info; } ;
struct TYPE_4__ {int state; } ;
struct TYPE_5__ {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 struct dm_table* dm_get_live_table_fast (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put_live_table_fast (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 int dm_table_any_congested (struct dm_table*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_any_congested(void *congested_data, int bdi_bits)
{
	int r = bdi_bits;
	struct mapped_device *md = congested_data;
	struct dm_table *map;

	if (!test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags)) {
		if (dm_request_based(md)) {
			/*
			 * With request-based DM we only need to check the
			 * top-level queue for congestion.
			 */
			r = md->queue->backing_dev_info->wb.state & bdi_bits;
		} else {
			map = dm_get_live_table_fast(md);
			if (map)
				r = dm_table_any_congested(map, bdi_bits);
			dm_put_live_table_fast(md);
		}
	}

	return r;
}