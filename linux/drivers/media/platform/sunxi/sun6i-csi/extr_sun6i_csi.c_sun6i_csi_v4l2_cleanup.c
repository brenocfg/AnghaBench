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
struct sun6i_csi {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  video; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun6i_video_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sun6i_csi_v4l2_cleanup(struct sun6i_csi *csi)
{
	media_device_unregister(&csi->media_dev);
	v4l2_async_notifier_unregister(&csi->notifier);
	v4l2_async_notifier_cleanup(&csi->notifier);
	sun6i_video_cleanup(&csi->video);
	v4l2_device_unregister(&csi->v4l2_dev);
	v4l2_ctrl_handler_free(&csi->ctrl_handler);
	media_device_cleanup(&csi->media_dev);
}