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
struct v4l2_subdev {int dummy; } ;
struct imx7_csi {int is_streaming; int /*<<< orphan*/  lock; int /*<<< orphan*/  src_sd; int /*<<< orphan*/  sink; } ;

/* Variables and functions */
 int EPIPE ; 
 int imx7_csi_streaming_start (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_streaming_stop (struct imx7_csi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int imx7_csi_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	int ret = 0;

	mutex_lock(&csi->lock);

	if (!csi->src_sd || !csi->sink) {
		ret = -EPIPE;
		goto out_unlock;
	}

	if (csi->is_streaming == !!enable)
		goto out_unlock;

	if (enable) {
		ret = v4l2_subdev_call(csi->src_sd, video, s_stream, 1);
		if (ret < 0)
			goto out_unlock;

		ret = imx7_csi_streaming_start(csi);
		if (ret < 0) {
			v4l2_subdev_call(csi->src_sd, video, s_stream, 0);
			goto out_unlock;
		}
	} else {
		imx7_csi_streaming_stop(csi);

		v4l2_subdev_call(csi->src_sd, video, s_stream, 0);
	}

	csi->is_streaming = !!enable;

out_unlock:
	mutex_unlock(&csi->lock);

	return ret;
}