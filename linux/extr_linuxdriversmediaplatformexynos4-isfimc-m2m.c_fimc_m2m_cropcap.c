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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {TYPE_1__ bounds; TYPE_1__ defrect; int /*<<< orphan*/  type; } ;
struct fimc_frame {int /*<<< orphan*/  o_height; int /*<<< orphan*/  o_width; } ;
struct fimc_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fimc_frame*) ; 
 int PTR_ERR (struct fimc_frame*) ; 
 struct fimc_frame* ctx_get_frame (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 struct fimc_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int fimc_m2m_cropcap(struct file *file, void *fh,
			    struct v4l2_cropcap *cr)
{
	struct fimc_ctx *ctx = fh_to_ctx(fh);
	struct fimc_frame *frame;

	frame = ctx_get_frame(ctx, cr->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	cr->bounds.left = 0;
	cr->bounds.top = 0;
	cr->bounds.width = frame->o_width;
	cr->bounds.height = frame->o_height;
	cr->defrect = cr->bounds;

	return 0;
}