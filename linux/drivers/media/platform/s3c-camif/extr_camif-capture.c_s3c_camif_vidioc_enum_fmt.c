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
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct camif_vp {int dummy; } ;
struct camif_fmt {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 struct camif_fmt* s3c_camif_find_format (struct camif_vp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_vidioc_enum_fmt(struct file *file, void *priv,
				     struct v4l2_fmtdesc *f)
{
	struct camif_vp *vp = video_drvdata(file);
	const struct camif_fmt *fmt;

	fmt = s3c_camif_find_format(vp, NULL, f->index);
	if (!fmt)
		return -EINVAL;

	f->pixelformat = fmt->fourcc;
	return 0;
}