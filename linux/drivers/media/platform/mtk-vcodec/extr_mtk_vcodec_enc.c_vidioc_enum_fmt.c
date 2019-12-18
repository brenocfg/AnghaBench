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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  reserved; int /*<<< orphan*/  pixelformat; } ;
struct mtk_video_fmt {scalar_t__ type; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MTK_FMT_ENC ; 
 scalar_t__ MTK_FMT_FRAME ; 
 int NUM_FORMATS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtk_video_fmt* mtk_video_formats ; 

__attribute__((used)) static int vidioc_enum_fmt(struct v4l2_fmtdesc *f, bool output_queue)
{
	const struct mtk_video_fmt *fmt;
	int i, j = 0;

	for (i = 0; i < NUM_FORMATS; ++i) {
		if (output_queue && mtk_video_formats[i].type != MTK_FMT_FRAME)
			continue;
		if (!output_queue && mtk_video_formats[i].type != MTK_FMT_ENC)
			continue;

		if (j == f->index) {
			fmt = &mtk_video_formats[i];
			f->pixelformat = fmt->fourcc;
			memset(f->reserved, 0, sizeof(f->reserved));
			return 0;
		}
		++j;
	}

	return -EINVAL;
}