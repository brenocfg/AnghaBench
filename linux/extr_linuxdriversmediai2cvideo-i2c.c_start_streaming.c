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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct video_i2c_data {scalar_t__ kthread_vid_cap; TYPE_1__ v4l2_dev; scalar_t__ sequence; } ;
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,struct video_i2c_data*,char*,int /*<<< orphan*/ ) ; 
 struct video_i2c_data* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_i2c_del_list (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_i2c_thread_vid_cap ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct video_i2c_data *data = vb2_get_drv_priv(vq);

	if (data->kthread_vid_cap)
		return 0;

	data->sequence = 0;
	data->kthread_vid_cap = kthread_run(video_i2c_thread_vid_cap, data,
					    "%s-vid-cap", data->v4l2_dev.name);
	if (!IS_ERR(data->kthread_vid_cap))
		return 0;

	video_i2c_del_list(vq, VB2_BUF_STATE_QUEUED);

	return PTR_ERR(data->kthread_vid_cap);
}