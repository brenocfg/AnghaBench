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
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int usbtv_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *f)
{
	if (f->index > 0)
		return -EINVAL;

	strlcpy(f->description, "16 bpp YUY2, 4:2:2, packed",
					sizeof(f->description));
	f->pixelformat = V4L2_PIX_FMT_YUYV;
	return 0;
}