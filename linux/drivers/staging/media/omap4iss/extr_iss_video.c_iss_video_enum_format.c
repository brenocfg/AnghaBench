#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct v4l2_fmtdesc {unsigned int index; scalar_t__ type; int /*<<< orphan*/  pixelformat; } ;
struct iss_video {scalar_t__ type; } ;
struct iss_format_info {scalar_t__ code; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct iss_format_info*) ; 
 int EINVAL ; 
 int __iss_video_get_format (struct iss_video*,struct v4l2_mbus_framefmt*) ; 
 struct iss_format_info* formats ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_enum_format(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
	struct iss_video *video = video_drvdata(file);
	struct v4l2_mbus_framefmt format;
	unsigned int index = f->index;
	unsigned int i;
	int ret;

	if (f->type != video->type)
		return -EINVAL;

	ret = __iss_video_get_format(video, &format);
	if (ret < 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(formats); ++i) {
		const struct iss_format_info *info = &formats[i];

		if (format.code != info->code)
			continue;

		if (index == 0) {
			f->pixelformat = info->pixelformat;
			return 0;
		}

		index--;
	}

	return -EINVAL;
}