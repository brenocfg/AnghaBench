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
typedef  int u32 ;
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct mtk_jpeg_fmt {int flags; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mtk_jpeg_enum_fmt(struct mtk_jpeg_fmt *mtk_jpeg_formats, int n,
			     struct v4l2_fmtdesc *f, u32 type)
{
	int i, num = 0;

	for (i = 0; i < n; ++i) {
		if (mtk_jpeg_formats[i].flags & type) {
			if (num == f->index)
				break;
			++num;
		}
	}

	if (i >= n)
		return -EINVAL;

	f->pixelformat = mtk_jpeg_formats[i].fourcc;

	return 0;
}