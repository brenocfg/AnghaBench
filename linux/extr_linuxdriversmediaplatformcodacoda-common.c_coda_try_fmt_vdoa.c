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
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;
struct coda_ctx {int /*<<< orphan*/  vdoa; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 
 int vdoa_context_configure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_try_fmt_vdoa(struct coda_ctx *ctx, struct v4l2_format *f,
			     bool *use_vdoa)
{
	int err;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (!use_vdoa)
		return -EINVAL;

	if (!ctx->vdoa) {
		*use_vdoa = false;
		return 0;
	}

	err = vdoa_context_configure(NULL, round_up(f->fmt.pix.width, 16),
				     f->fmt.pix.height, f->fmt.pix.pixelformat);
	if (err) {
		*use_vdoa = false;
		return 0;
	}

	*use_vdoa = true;
	return 0;
}