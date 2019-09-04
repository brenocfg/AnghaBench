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
struct TYPE_3__ {scalar_t__ pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix_mp; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct mtk_video_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int NUM_FORMATS ; 
 struct mtk_video_fmt* mtk_video_formats ; 

__attribute__((used)) static struct mtk_video_fmt *mtk_vdec_find_format(struct v4l2_format *f)
{
	struct mtk_video_fmt *fmt;
	unsigned int k;

	for (k = 0; k < NUM_FORMATS; k++) {
		fmt = &mtk_video_formats[k];
		if (fmt->fourcc == f->fmt.pix_mp.pixelformat)
			return fmt;
	}

	return NULL;
}