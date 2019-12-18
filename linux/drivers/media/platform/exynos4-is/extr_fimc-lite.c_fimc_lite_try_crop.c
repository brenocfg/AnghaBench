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
struct v4l2_rect {scalar_t__ height; scalar_t__ width; void* top; void* left; } ;
struct flite_frame {scalar_t__ f_height; scalar_t__ f_width; } ;
struct fimc_lite {int /*<<< orphan*/  subdev; TYPE_1__* dd; struct flite_frame inp_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  win_hor_offs_align; } ;

/* Variables and functions */
 void* clamp_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debug ; 
 void* round_down (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void*,void*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_lite_try_crop(struct fimc_lite *fimc, struct v4l2_rect *r)
{
	struct flite_frame *frame = &fimc->inp_frame;

	v4l_bound_align_image(&r->width, 0, frame->f_width, 0,
			      &r->height, 0, frame->f_height, 0, 0);

	/* Adjust left/top if cropping rectangle got out of bounds */
	r->left = clamp_t(u32, r->left, 0, frame->f_width - r->width);
	r->left = round_down(r->left, fimc->dd->win_hor_offs_align);
	r->top  = clamp_t(u32, r->top, 0, frame->f_height - r->height);

	v4l2_dbg(1, debug, &fimc->subdev, "(%d,%d)/%dx%d, sink fmt: %dx%d\n",
		 r->left, r->top, r->width, r->height,
		 frame->f_width, frame->f_height);
}