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
struct TYPE_3__ {int /*<<< orphan*/  pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  pixfmt; } ;
struct fimc_isp {TYPE_2__ video_capture; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_g_fmt_mplane(struct file *file, void *fh,
					struct v4l2_format *f)
{
	struct fimc_isp *isp = video_drvdata(file);

	f->fmt.pix_mp = isp->video_capture.pixfmt;
	return 0;
}