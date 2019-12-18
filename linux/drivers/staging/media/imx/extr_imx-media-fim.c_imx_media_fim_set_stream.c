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
struct v4l2_fract {int dummy; } ;
struct imx_media_fim {int stream_on; int /*<<< orphan*/ * ctrl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t FIM_CL_ENABLE ; 
 int /*<<< orphan*/  fim_acquire_first_ts (struct imx_media_fim*) ; 
 int /*<<< orphan*/  fim_free_input_capture (struct imx_media_fim*) ; 
 int fim_request_input_capture (struct imx_media_fim*) ; 
 scalar_t__ icap_enabled (struct imx_media_fim*) ; 
 int /*<<< orphan*/  reset_fim (struct imx_media_fim*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_fim_nominal (struct imx_media_fim*,struct v4l2_fract const*) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (int /*<<< orphan*/ ) ; 

int imx_media_fim_set_stream(struct imx_media_fim *fim,
			     const struct v4l2_fract *fi,
			     bool on)
{
	unsigned long flags;
	int ret = 0;

	v4l2_ctrl_lock(fim->ctrl[FIM_CL_ENABLE]);

	if (fim->stream_on == on)
		goto out;

	if (on) {
		spin_lock_irqsave(&fim->lock, flags);
		reset_fim(fim, true);
		update_fim_nominal(fim, fi);
		spin_unlock_irqrestore(&fim->lock, flags);

		if (icap_enabled(fim)) {
			ret = fim_request_input_capture(fim);
			if (ret)
				goto out;
			fim_acquire_first_ts(fim);
		}
	} else {
		if (icap_enabled(fim))
			fim_free_input_capture(fim);
	}

	fim->stream_on = on;
out:
	v4l2_ctrl_unlock(fim->ctrl[FIM_CL_ENABLE]);
	return ret;
}