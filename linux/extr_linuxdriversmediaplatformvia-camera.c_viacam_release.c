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
struct via_camera {scalar_t__ users; scalar_t__ opstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  vb_queue; struct file* owner; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_IDLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_sensor_power_down (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_stop_engine (struct via_camera*) ; 
 int /*<<< orphan*/  viafb_release_dma () ; 
 struct via_camera* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_release(struct file *filp)
{
	struct via_camera *cam = video_drvdata(filp);

	mutex_lock(&cam->lock);
	(cam->users)--;
	/*
	 * If the "owner" is closing, shut down any ongoing
	 * operations.
	 */
	if (filp == cam->owner) {
		videobuf_stop(&cam->vb_queue);
		/*
		 * We don't hold the spinlock here, but, if release()
		 * is being called by the owner, nobody else will
		 * be changing the state.  And an extra stop would
		 * not hurt anyway.
		 */
		if (cam->opstate != S_IDLE)
			viacam_stop_engine(cam);
		cam->owner = NULL;
	}
	/*
	 * Last one out needs to turn out the lights.
	 */
	if (cam->users == 0) {
		videobuf_mmap_free(&cam->vb_queue);
		via_sensor_power_down(cam);
		viafb_release_dma();
	}
	mutex_unlock(&cam->lock);
	return 0;
}