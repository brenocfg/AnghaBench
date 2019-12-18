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
struct TYPE_3__ {struct media_device* mdev; } ;
struct TYPE_4__ {TYPE_1__ graph_obj; } ;
struct video_device {TYPE_2__ entity; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; int /*<<< orphan*/  (* disable_source ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void v4l_disable_media_source(struct video_device *vdev)
{
	struct media_device *mdev = vdev->entity.graph_obj.mdev;

	if (mdev) {
		mutex_lock(&mdev->graph_mutex);
		if (mdev->disable_source)
			mdev->disable_source(&vdev->entity);
		mutex_unlock(&mdev->graph_mutex);
	}
}