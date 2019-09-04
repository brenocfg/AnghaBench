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
struct ov2680_dev {int is_streaming; int /*<<< orphan*/  lock; scalar_t__ mode_pending_changes; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov2680_mode_set (struct ov2680_dev*) ; 
 int ov2680_stream_disable (struct ov2680_dev*) ; 
 int ov2680_stream_enable (struct ov2680_dev*) ; 
 struct ov2680_dev* to_ov2680_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2680_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov2680_dev *sensor = to_ov2680_dev(sd);
	int ret = 0;

	mutex_lock(&sensor->lock);

	if (sensor->is_streaming == !!enable)
		goto unlock;

	if (enable && sensor->mode_pending_changes) {
		ret = ov2680_mode_set(sensor);
		if (ret < 0)
			goto unlock;
	}

	if (enable)
		ret = ov2680_stream_enable(sensor);
	else
		ret = ov2680_stream_disable(sensor);

	sensor->is_streaming = !!enable;

unlock:
	mutex_unlock(&sensor->lock);

	return ret;
}