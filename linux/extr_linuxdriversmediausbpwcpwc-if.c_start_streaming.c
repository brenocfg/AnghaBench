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
struct vb2_queue {int dummy; } ;
struct pwc_device {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/ * leds ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwc_camera_power (struct pwc_device*,int) ; 
 int /*<<< orphan*/  pwc_cleanup_queued_bufs (struct pwc_device*,int /*<<< orphan*/ ) ; 
 int pwc_isoc_init (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_set_leds (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pwc_device* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct pwc_device *pdev = vb2_get_drv_priv(vq);
	int r;

	if (!pdev->udev)
		return -ENODEV;

	if (mutex_lock_interruptible(&pdev->v4l2_lock))
		return -ERESTARTSYS;
	/* Turn on camera and set LEDS on */
	pwc_camera_power(pdev, 1);
	pwc_set_leds(pdev, leds[0], leds[1]);

	r = pwc_isoc_init(pdev);
	if (r) {
		/* If we failed turn camera and LEDS back off */
		pwc_set_leds(pdev, 0, 0);
		pwc_camera_power(pdev, 0);
		/* And cleanup any queued bufs!! */
		pwc_cleanup_queued_bufs(pdev, VB2_BUF_STATE_QUEUED);
	}
	mutex_unlock(&pdev->v4l2_lock);

	return r;
}