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
struct videobuf_buffer {int dummy; } ;
struct via_camera {scalar_t__ users; int /*<<< orphan*/  lock; TYPE_2__* viadev; TYPE_1__* platdev; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  flags; } ;
struct file {struct via_camera* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONFIG_NEEDED ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_sensor_power_up (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_vb_ops ; 
 int viafb_request_dma () ; 
 struct via_camera* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_queue_sg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct via_camera*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_open(struct file *filp)
{
	struct via_camera *cam = video_drvdata(filp);

	filp->private_data = cam;
	/*
	 * Note the new user.  If this is the first one, we'll also
	 * need to power up the sensor.
	 */
	mutex_lock(&cam->lock);
	if (cam->users == 0) {
		int ret = viafb_request_dma();

		if (ret) {
			mutex_unlock(&cam->lock);
			return ret;
		}
		via_sensor_power_up(cam);
		set_bit(CF_CONFIG_NEEDED, &cam->flags);
		/*
		 * Hook into videobuf.	Evidently this cannot fail.
		 */
		videobuf_queue_sg_init(&cam->vb_queue, &viacam_vb_ops,
				&cam->platdev->dev, &cam->viadev->reg_lock,
				V4L2_BUF_TYPE_VIDEO_CAPTURE, V4L2_FIELD_NONE,
				sizeof(struct videobuf_buffer), cam, NULL);
	}
	(cam->users)++;
	mutex_unlock(&cam->lock);
	return 0;
}