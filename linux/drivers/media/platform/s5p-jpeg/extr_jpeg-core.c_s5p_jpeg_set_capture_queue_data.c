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
struct s5p_jpeg_q_data {int w; int h; int size; TYPE_2__* fmt; } ;
struct TYPE_3__ {int w; int h; } ;
struct s5p_jpeg_ctx {TYPE_1__ out_q; struct s5p_jpeg_q_data cap_q; } ;
struct TYPE_4__ {int depth; int /*<<< orphan*/  v_align; int /*<<< orphan*/  h_align; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_JPEG_MAX_HEIGHT ; 
 int /*<<< orphan*/  S5P_JPEG_MAX_WIDTH ; 
 int /*<<< orphan*/  S5P_JPEG_MIN_HEIGHT ; 
 int /*<<< orphan*/  S5P_JPEG_MIN_WIDTH ; 
 int /*<<< orphan*/  jpeg_bound_align_image (struct s5p_jpeg_ctx*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_jpeg_set_capture_queue_data(struct s5p_jpeg_ctx *ctx)
{
	struct s5p_jpeg_q_data *q_data = &ctx->cap_q;

	q_data->w = ctx->out_q.w;
	q_data->h = ctx->out_q.h;

	/*
	 * This call to jpeg_bound_align_image() takes care of width and
	 * height values alignment when user space calls the QBUF of
	 * OUTPUT buffer after the S_FMT of CAPTURE buffer.
	 * Please note that on Exynos4x12 SoCs, resigning from executing
	 * S_FMT on capture buffer for each JPEG image can result in a
	 * hardware hangup if subsampling is lower than the one of input
	 * JPEG.
	 */
	jpeg_bound_align_image(ctx, &q_data->w, S5P_JPEG_MIN_WIDTH,
			       S5P_JPEG_MAX_WIDTH, q_data->fmt->h_align,
			       &q_data->h, S5P_JPEG_MIN_HEIGHT,
			       S5P_JPEG_MAX_HEIGHT, q_data->fmt->v_align);

	q_data->size = q_data->w * q_data->h * q_data->fmt->depth >> 3;
}