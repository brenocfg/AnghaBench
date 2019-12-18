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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct TYPE_4__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct isi_format {int /*<<< orphan*/  mbus_code; } ;
struct TYPE_3__ {int /*<<< orphan*/  subdev; } ;
struct atmel_isi {struct isi_format const* current_fmt; struct v4l2_format fmt; TYPE_1__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int isi_try_fmt (struct atmel_isi*,struct v4l2_format*,struct isi_format const**) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int isi_set_fmt(struct atmel_isi *isi, struct v4l2_format *f)
{
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	const struct isi_format *current_fmt;
	int ret;

	ret = isi_try_fmt(isi, f, &current_fmt);
	if (ret)
		return ret;

	v4l2_fill_mbus_format(&format.format, &f->fmt.pix,
			      current_fmt->mbus_code);
	ret = v4l2_subdev_call(isi->entity.subdev, pad,
			       set_fmt, NULL, &format);
	if (ret < 0)
		return ret;

	isi->fmt = *f;
	isi->current_fmt = current_fmt;

	return 0;
}