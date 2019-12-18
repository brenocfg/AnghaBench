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
struct v4l2_rect {scalar_t__ height; scalar_t__ width; void* top; void* left; } ;
struct flite_frame {scalar_t__ f_height; scalar_t__ f_width; } ;
struct TYPE_3__ {struct v4l2_rect rect; } ;
struct fimc_lite {int /*<<< orphan*/  subdev; struct flite_frame out_frame; TYPE_2__* dd; TYPE_1__ inp_frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  out_hor_offs_align; } ;

/* Variables and functions */
 void* clamp_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debug ; 
 void* round_down (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void*,void*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void fimc_lite_try_compose(struct fimc_lite *fimc, struct v4l2_rect *r)
{
	struct flite_frame *frame = &fimc->out_frame;
	struct v4l2_rect *crop_rect = &fimc->inp_frame.rect;

	/* Scaling is not supported so we enforce compose rectangle size
	   same as size of the sink crop rectangle. */
	r->width = crop_rect->width;
	r->height = crop_rect->height;

	/* Adjust left/top if the composing rectangle got out of bounds */
	r->left = clamp_t(u32, r->left, 0, frame->f_width - r->width);
	r->left = round_down(r->left, fimc->dd->out_hor_offs_align);
	r->top  = clamp_t(u32, r->top, 0, fimc->out_frame.f_height - r->height);

	v4l2_dbg(1, debug, &fimc->subdev, "(%d,%d)/%dx%d, source fmt: %dx%d\n",
		 r->left, r->top, r->width, r->height,
		 frame->f_width, frame->f_height);
}