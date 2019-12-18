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
struct vb2_queue {struct fimc_ctx* drv_priv; } ;
struct fimc_vid_cap {int reqbufs_count; int active_buf_cnt; int /*<<< orphan*/  ve; scalar_t__ frame_count; } ;
struct fimc_dev {int /*<<< orphan*/  state; struct fimc_vid_cap vid_cap; } ;
struct fimc_ctx {struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CAPT_ISP_STREAM ; 
 int /*<<< orphan*/  ST_CAPT_PEND ; 
 int /*<<< orphan*/  ST_CAPT_STREAM ; 
 int /*<<< orphan*/  fimc_activate_capture (struct fimc_ctx*) ; 
 int fimc_capture_hw_init (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_capture_state_cleanup (struct fimc_dev*,int) ; 
 int fimc_pipeline_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_stream ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct fimc_ctx *ctx = q->drv_priv;
	struct fimc_dev *fimc = ctx->fimc_dev;
	struct fimc_vid_cap *vid_cap = &fimc->vid_cap;
	int min_bufs;
	int ret;

	vid_cap->frame_count = 0;

	ret = fimc_capture_hw_init(fimc);
	if (ret) {
		fimc_capture_state_cleanup(fimc, false);
		return ret;
	}

	set_bit(ST_CAPT_PEND, &fimc->state);

	min_bufs = fimc->vid_cap.reqbufs_count > 1 ? 2 : 1;

	if (vid_cap->active_buf_cnt >= min_bufs &&
	    !test_and_set_bit(ST_CAPT_STREAM, &fimc->state)) {
		fimc_activate_capture(ctx);

		if (!test_and_set_bit(ST_CAPT_ISP_STREAM, &fimc->state))
			return fimc_pipeline_call(&vid_cap->ve, set_stream, 1);
	}

	return 0;
}