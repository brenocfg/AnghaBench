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
struct v4l2_crop {int /*<<< orphan*/  c; int /*<<< orphan*/  type; } ;
struct gsc_frame {int /*<<< orphan*/  crop; } ;
struct gsc_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gsc_frame*) ; 
 int PTR_ERR (struct gsc_frame*) ; 
 struct gsc_frame* ctx_get_frame (struct gsc_ctx*,int /*<<< orphan*/ ) ; 

int gsc_g_crop(struct gsc_ctx *ctx, struct v4l2_crop *cr)
{
	struct gsc_frame *frame;

	frame = ctx_get_frame(ctx, cr->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	cr->c = frame->crop;

	return 0;
}