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
struct video_i2c_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * kthread_vid_cap; } ;
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 struct video_i2c_data* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_i2c_del_list (struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *vq)
{
	struct video_i2c_data *data = vb2_get_drv_priv(vq);

	if (data->kthread_vid_cap == NULL)
		return;

	kthread_stop(data->kthread_vid_cap);
	data->kthread_vid_cap = NULL;
	pm_runtime_mark_last_busy(regmap_get_device(data->regmap));
	pm_runtime_put_autosuspend(regmap_get_device(data->regmap));

	video_i2c_del_list(vq, VB2_BUF_STATE_ERROR);
}