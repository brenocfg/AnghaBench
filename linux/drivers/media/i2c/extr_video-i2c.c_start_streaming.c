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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct video_i2c_data {scalar_t__ kthread_vid_cap; TYPE_2__ v4l2_dev; scalar_t__ sequence; TYPE_1__* chip; int /*<<< orphan*/  regmap; } ;
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int (* setup ) (struct video_i2c_data*) ;} ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (scalar_t__) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,struct video_i2c_data*,char*,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int stub1 (struct video_i2c_data*) ; 
 struct video_i2c_data* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_i2c_del_list (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_i2c_thread_vid_cap ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct video_i2c_data *data = vb2_get_drv_priv(vq);
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	if (data->kthread_vid_cap)
		return 0;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		pm_runtime_put_noidle(dev);
		goto error_del_list;
	}

	ret = data->chip->setup(data);
	if (ret)
		goto error_rpm_put;

	data->sequence = 0;
	data->kthread_vid_cap = kthread_run(video_i2c_thread_vid_cap, data,
					    "%s-vid-cap", data->v4l2_dev.name);
	ret = PTR_ERR_OR_ZERO(data->kthread_vid_cap);
	if (!ret)
		return 0;

error_rpm_put:
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
error_del_list:
	video_i2c_del_list(vq, VB2_BUF_STATE_QUEUED);

	return ret;
}