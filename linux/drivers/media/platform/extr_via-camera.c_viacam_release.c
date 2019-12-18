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
struct via_camera {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  via_sensor_power_down (struct via_camera*) ; 
 int /*<<< orphan*/  viafb_release_dma () ; 
 struct via_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int viacam_release(struct file *filp)
{
	struct via_camera *cam = video_drvdata(filp);
	bool last_open;

	mutex_lock(&cam->lock);
	last_open = v4l2_fh_is_singular_file(filp);
	_vb2_fop_release(filp, NULL);
	/*
	 * Last one out needs to turn out the lights.
	 */
	if (last_open) {
		via_sensor_power_down(cam);
		viafb_release_dma();
	}
	mutex_unlock(&cam->lock);
	return 0;
}