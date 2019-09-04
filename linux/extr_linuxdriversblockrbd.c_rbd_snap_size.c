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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__ image_size; scalar_t__* snap_sizes; } ;
struct rbd_device {int image_format; TYPE_1__ header; } ;

/* Variables and functions */
 size_t BAD_SNAP_INDEX ; 
 scalar_t__ CEPH_NOSNAP ; 
 int ENOENT ; 
 int _rbd_dev_v2_snap_size (struct rbd_device*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 size_t rbd_dev_snap_index (struct rbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  rbd_image_format_valid (int) ; 

__attribute__((used)) static int rbd_snap_size(struct rbd_device *rbd_dev, u64 snap_id,
				u64 *snap_size)
{
	rbd_assert(rbd_image_format_valid(rbd_dev->image_format));
	if (snap_id == CEPH_NOSNAP) {
		*snap_size = rbd_dev->header.image_size;
	} else if (rbd_dev->image_format == 1) {
		u32 which;

		which = rbd_dev_snap_index(rbd_dev, snap_id);
		if (which == BAD_SNAP_INDEX)
			return -ENOENT;

		*snap_size = rbd_dev->header.snap_sizes[which];
	} else {
		u64 size = 0;
		int ret;

		ret = _rbd_dev_v2_snap_size(rbd_dev, snap_id, NULL, &size);
		if (ret)
			return ret;

		*snap_size = size;
	}
	return 0;
}