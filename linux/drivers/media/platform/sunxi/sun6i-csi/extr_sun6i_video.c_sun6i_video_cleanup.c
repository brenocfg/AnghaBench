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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct sun6i_video {int /*<<< orphan*/  lock; int /*<<< orphan*/  vb2_vidq; TYPE_1__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void sun6i_video_cleanup(struct sun6i_video *video)
{
	video_unregister_device(&video->vdev);
	media_entity_cleanup(&video->vdev.entity);
	vb2_queue_release(&video->vb2_vidq);
	mutex_destroy(&video->lock);
}