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
struct via_camera {scalar_t__ opstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  qos_request; int /*<<< orphan*/  flags; struct file* owner; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONFIG_NEEDED ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 scalar_t__ S_IDLE ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int viacam_config_controller (struct via_camera*) ; 
 int viacam_configure_sensor (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_start_engine (struct via_camera*) ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_streamon(struct file *filp, void *priv, enum v4l2_buf_type t)
{
	struct via_camera *cam = priv;
	int ret = 0;

	if (t != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	mutex_lock(&cam->lock);
	if (cam->opstate != S_IDLE) {
		ret = -EBUSY;
		goto out;
	}
	/*
	 * Enforce the V4l2 "only one owner gets to read data" rule.
	 */
	if (cam->owner && cam->owner != filp) {
		ret = -EBUSY;
		goto out;
	}
	cam->owner = filp;
	/*
	 * Configure things if need be.
	 */
	if (test_bit(CF_CONFIG_NEEDED, &cam->flags)) {
		ret = viacam_configure_sensor(cam);
		if (ret)
			goto out;
		ret = viacam_config_controller(cam);
		if (ret)
			goto out;
	}
	/*
	 * If the CPU goes into C3, the DMA transfer gets corrupted and
	 * users start filing unsightly bug reports.  Put in a "latency"
	 * requirement which will keep the CPU out of the deeper sleep
	 * states.
	 */
	pm_qos_add_request(&cam->qos_request, PM_QOS_CPU_DMA_LATENCY, 50);
	/*
	 * Fire things up.
	 */
	INIT_LIST_HEAD(&cam->buffer_queue);
	ret = videobuf_streamon(&cam->vb_queue);
	if (!ret)
		viacam_start_engine(cam);
out:
	mutex_unlock(&cam->lock);
	return ret;
}