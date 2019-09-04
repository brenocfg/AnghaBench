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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct omap_vout_device {int /*<<< orphan*/  pix; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vidioc_g_fmt_vid_out(struct file *file, void *fh,
			struct v4l2_format *f)
{
	struct omap_vout_device *vout = fh;

	f->fmt.pix = vout->pix;
	return 0;

}