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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_crop {TYPE_1__ c; int /*<<< orphan*/  type; } ;
struct fimc_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  offs_v; int /*<<< orphan*/  offs_h; } ;
struct fimc_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fimc_frame*) ; 
 int PTR_ERR (struct fimc_frame*) ; 
 struct fimc_frame* ctx_get_frame (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 struct fimc_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int fimc_m2m_g_crop(struct file *file, void *fh, struct v4l2_crop *cr)
{
	struct fimc_ctx *ctx = fh_to_ctx(fh);
	struct fimc_frame *frame;

	frame = ctx_get_frame(ctx, cr->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	cr->c.left = frame->offs_h;
	cr->c.top = frame->offs_v;
	cr->c.width = frame->width;
	cr->c.height = frame->height;

	return 0;
}