#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct mtk_video_fmt {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 size_t CAP_FMT_IDX ; 
 struct mtk_video_fmt* mtk_vdec_find_format (struct v4l2_format*) ; 
 TYPE_3__* mtk_video_formats ; 
 int vidioc_try_fmt (struct v4l2_format*,struct mtk_video_fmt const*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap_mplane(struct file *file, void *priv,
				struct v4l2_format *f)
{
	const struct mtk_video_fmt *fmt;

	fmt = mtk_vdec_find_format(f);
	if (!fmt) {
		f->fmt.pix.pixelformat = mtk_video_formats[CAP_FMT_IDX].fourcc;
		fmt = mtk_vdec_find_format(f);
	}

	return vidioc_try_fmt(f, fmt);
}