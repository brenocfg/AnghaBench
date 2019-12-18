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
struct mcam_camera {scalar_t__ buffer_mode; int /*<<< orphan*/  s_mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ B_vmalloc ; 
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 scalar_t__ alloc_bufs_at_read ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mcam_clk_disable (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_disable_mipi (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_free_dma_bufs (struct mcam_camera*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  sensor_call (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 struct mcam_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int mcam_v4l_release(struct file *filp)
{
	struct mcam_camera *cam = video_drvdata(filp);
	bool last_open;

	mutex_lock(&cam->s_mutex);
	last_open = v4l2_fh_is_singular_file(filp);
	_vb2_fop_release(filp, NULL);
	if (last_open) {
		mcam_disable_mipi(cam);
		sensor_call(cam, core, s_power, 0);
		mcam_clk_disable(cam);
		if (cam->buffer_mode == B_vmalloc && alloc_bufs_at_read)
			mcam_free_dma_bufs(cam);
	}

	mutex_unlock(&cam->s_mutex);
	return 0;
}