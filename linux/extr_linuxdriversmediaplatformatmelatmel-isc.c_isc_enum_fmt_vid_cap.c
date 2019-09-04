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
typedef  size_t u32 ;
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct isc_device {size_t num_user_formats; TYPE_1__** user_formats; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_enum_fmt_vid_cap(struct file *file, void *priv,
				 struct v4l2_fmtdesc *f)
{
	struct isc_device *isc = video_drvdata(file);
	u32 index = f->index;

	if (index >= isc->num_user_formats)
		return -EINVAL;

	f->pixelformat = isc->user_formats[index]->fourcc;

	return 0;
}