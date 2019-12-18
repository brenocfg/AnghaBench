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
struct v4l2_format {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ctx; } ;
struct fimc_dev {TYPE_2__ vid_cap; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fimc_get_format (int /*<<< orphan*/ *,struct v4l2_format*) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_cap_g_fmt_mplane(struct file *file, void *fh,
				 struct v4l2_format *f)
{
	struct fimc_dev *fimc = video_drvdata(file);

	__fimc_get_format(&fimc->vid_cap.ctx->d_frame, f);
	return 0;
}