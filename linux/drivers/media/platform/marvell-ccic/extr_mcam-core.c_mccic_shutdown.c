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
struct TYPE_2__ {int /*<<< orphan*/  fh_list; } ;
struct mcam_camera {scalar_t__ buffer_mode; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; int /*<<< orphan*/  ctrl_handler; TYPE_1__ vdev; } ;

/* Variables and functions */
 scalar_t__ B_vmalloc ; 
 int /*<<< orphan*/  cam_warn (struct mcam_camera*,char*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcam_free_dma_bufs (struct mcam_camera*) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  sensor_call (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void mccic_shutdown(struct mcam_camera *cam)
{
	/*
	 * If we have no users (and we really, really should have no
	 * users) the device will already be powered down.  Trying to
	 * take it down again will wedge the machine, which is frowned
	 * upon.
	 */
	if (!list_empty(&cam->vdev.fh_list)) {
		cam_warn(cam, "Removing a device with users!\n");
		sensor_call(cam, core, s_power, 0);
	}
	if (cam->buffer_mode == B_vmalloc)
		mcam_free_dma_bufs(cam);
	v4l2_ctrl_handler_free(&cam->ctrl_handler);
	v4l2_async_notifier_unregister(&cam->notifier);
	v4l2_device_unregister(&cam->v4l2_dev);
}