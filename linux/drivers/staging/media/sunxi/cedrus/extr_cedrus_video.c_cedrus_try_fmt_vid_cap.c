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
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cedrus_dev {int /*<<< orphan*/  capabilities; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_DECODE_DST ; 
 int EINVAL ; 
 int /*<<< orphan*/  cedrus_check_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cedrus_ctx* cedrus_file2ctx (struct file*) ; 
 int /*<<< orphan*/  cedrus_prepare_format (struct v4l2_pix_format*) ; 

__attribute__((used)) static int cedrus_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct cedrus_ctx *ctx = cedrus_file2ctx(file);
	struct cedrus_dev *dev = ctx->dev;
	struct v4l2_pix_format *pix_fmt = &f->fmt.pix;

	if (!cedrus_check_format(pix_fmt->pixelformat, CEDRUS_DECODE_DST,
				 dev->capabilities))
		return -EINVAL;

	cedrus_prepare_format(pix_fmt);

	return 0;
}