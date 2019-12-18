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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_frame_desc {int num_entries; TYPE_3__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_size; } ;
struct m5mols_info {int /*<<< orphan*/  lock; TYPE_2__* ffmt; TYPE_1__ cap; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  pixelcode; int /*<<< orphan*/  length; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t M5MOLS_RESTYPE_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MBUS_FRAME_DESC_FL_LEN_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 

__attribute__((used)) static int m5mols_get_frame_desc(struct v4l2_subdev *sd, unsigned int pad,
				 struct v4l2_mbus_frame_desc *fd)
{
	struct m5mols_info *info = to_m5mols(sd);

	if (pad != 0 || fd == NULL)
		return -EINVAL;

	mutex_lock(&info->lock);
	/*
	 * .get_frame_desc is only used for compressed formats,
	 * thus we always return the capture frame parameters here.
	 */
	fd->entry[0].length = info->cap.buf_size;
	fd->entry[0].pixelcode = info->ffmt[M5MOLS_RESTYPE_CAPTURE].code;
	mutex_unlock(&info->lock);

	fd->entry[0].flags = V4L2_MBUS_FRAME_DESC_FL_LEN_MAX;
	fd->num_entries = 1;

	return 0;
}