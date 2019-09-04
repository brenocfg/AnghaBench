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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct isi_format {int /*<<< orphan*/  mbus_code; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct atmel_isi {TYPE_1__ entity; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct isi_format* find_format_by_fourcc (struct atmel_isi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct atmel_isi* video_drvdata (struct file*) ; 

__attribute__((used)) static int isi_enum_frameintervals(struct file *file, void *fh,
				    struct v4l2_frmivalenum *fival)
{
	struct atmel_isi *isi = video_drvdata(file);
	const struct isi_format *isi_fmt;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	isi_fmt = find_format_by_fourcc(isi, fival->pixel_format);
	if (!isi_fmt)
		return -EINVAL;

	fie.code = isi_fmt->mbus_code;

	ret = v4l2_subdev_call(isi->entity.subdev, pad,
			       enum_frame_interval, NULL, &fie);
	if (ret)
		return ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}