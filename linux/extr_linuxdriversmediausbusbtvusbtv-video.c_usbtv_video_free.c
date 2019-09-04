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
struct usbtv {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vb2q_lock; int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbtv_stop (struct usbtv*) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void usbtv_video_free(struct usbtv *usbtv)
{
	mutex_lock(&usbtv->vb2q_lock);
	mutex_lock(&usbtv->v4l2_lock);

	usbtv_stop(usbtv);
	video_unregister_device(&usbtv->vdev);
	v4l2_device_disconnect(&usbtv->v4l2_dev);

	mutex_unlock(&usbtv->v4l2_lock);
	mutex_unlock(&usbtv->vb2q_lock);

	v4l2_device_put(&usbtv->v4l2_dev);
}