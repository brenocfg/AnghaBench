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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct unicam_fmt {int /*<<< orphan*/  fourcc; } ;
struct unicam_device {size_t num_active_fmt; struct unicam_fmt* active_fmts; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_enum_fmt_vid_cap(struct file *file, void  *priv,
				   struct v4l2_fmtdesc *f)
{
	struct unicam_device *dev = video_drvdata(file);
	const struct unicam_fmt *fmt = NULL;

	if (f->index >= dev->num_active_fmt)
		return -EINVAL;

	fmt = &dev->active_fmts[f->index];

	f->pixelformat = fmt->fourcc;

	return 0;
}