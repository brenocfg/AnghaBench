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
struct via_camera {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONFIG_NEEDED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int /*<<< orphan*/  via_sensor_power_up (struct via_camera*) ; 
 int viafb_request_dma () ; 
 struct via_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int viacam_open(struct file *filp)
{
	struct via_camera *cam = video_drvdata(filp);
	int ret;

	/*
	 * Note the new user.  If this is the first one, we'll also
	 * need to power up the sensor.
	 */
	mutex_lock(&cam->lock);
	ret = v4l2_fh_open(filp);
	if (ret)
		goto out;
	if (v4l2_fh_is_singular_file(filp)) {
		ret = viafb_request_dma();

		if (ret) {
			v4l2_fh_release(filp);
			goto out;
		}
		via_sensor_power_up(cam);
		set_bit(CF_CONFIG_NEEDED, &cam->flags);
	}
out:
	mutex_unlock(&cam->lock);
	return ret;
}