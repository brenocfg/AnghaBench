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
struct vb2_queue {int dummy; } ;
struct pwc_device {int /*<<< orphan*/  v4l2_lock; TYPE_1__* fill_buf; scalar_t__ udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_3__ {TYPE_2__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwc_camera_power (struct pwc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwc_cleanup_queued_bufs (struct pwc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwc_isoc_cleanup (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_set_leds (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pwc_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *vq)
{
	struct pwc_device *pdev = vb2_get_drv_priv(vq);

	mutex_lock(&pdev->v4l2_lock);
	if (pdev->udev) {
		pwc_set_leds(pdev, 0, 0);
		pwc_camera_power(pdev, 0);
		pwc_isoc_cleanup(pdev);
	}

	pwc_cleanup_queued_bufs(pdev, VB2_BUF_STATE_ERROR);
	if (pdev->fill_buf)
		vb2_buffer_done(&pdev->fill_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	mutex_unlock(&pdev->v4l2_lock);
}