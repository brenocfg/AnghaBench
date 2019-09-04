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
struct video_i2c_data {TYPE_1__* chip; } ;
struct v4l2_fmtdesc {int type; scalar_t__ index; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {struct v4l2_fmtdesc* format; } ;

/* Variables and functions */
 int EINVAL ; 
 struct video_i2c_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_i2c_enum_fmt_vid_cap(struct file *file, void *fh,
					struct v4l2_fmtdesc *fmt)
{
	struct video_i2c_data *data = video_drvdata(file);
	enum v4l2_buf_type type = fmt->type;

	if (fmt->index > 0)
		return -EINVAL;

	*fmt = *data->chip->format;
	fmt->type = type;

	return 0;
}