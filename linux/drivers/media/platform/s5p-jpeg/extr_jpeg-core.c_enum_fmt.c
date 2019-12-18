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
typedef  int u32 ;
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct s5p_jpeg_fmt {int flags; int /*<<< orphan*/  fourcc; } ;
struct s5p_jpeg_ctx {TYPE_2__* jpeg; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {unsigned int fmt_ver_flag; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int enum_fmt(struct s5p_jpeg_ctx *ctx,
		    struct s5p_jpeg_fmt *sjpeg_formats, int n,
		    struct v4l2_fmtdesc *f, u32 type)
{
	int i, num = 0;
	unsigned int fmt_ver_flag = ctx->jpeg->variant->fmt_ver_flag;

	for (i = 0; i < n; ++i) {
		if (sjpeg_formats[i].flags & type &&
		    sjpeg_formats[i].flags & fmt_ver_flag) {
			/* index-th format of type type found ? */
			if (num == f->index)
				break;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index
			 */
			++num;
		}
	}

	/* Format not found */
	if (i >= n)
		return -EINVAL;

	f->pixelformat = sjpeg_formats[i].fourcc;

	return 0;
}