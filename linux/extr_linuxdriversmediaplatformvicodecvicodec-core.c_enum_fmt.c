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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_FWHT ; 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 scalar_t__ multiplanar ; 
 int /*<<< orphan*/ * pixfmts_yuv ; 

__attribute__((used)) static int enum_fmt(struct v4l2_fmtdesc *f, bool is_enc, bool is_out)
{
	bool is_yuv = (is_enc && is_out) || (!is_enc && !is_out);

	if (V4L2_TYPE_IS_MULTIPLANAR(f->type) && !multiplanar)
		return -EINVAL;
	if (!V4L2_TYPE_IS_MULTIPLANAR(f->type) && multiplanar)
		return -EINVAL;
	if (f->index >= (is_yuv ? ARRAY_SIZE(pixfmts_yuv) : 1))
		return -EINVAL;

	if (is_yuv)
		f->pixelformat = pixfmts_yuv[f->index];
	else
		f->pixelformat = V4L2_PIX_FMT_FWHT;
	return 0;
}