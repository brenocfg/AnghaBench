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
struct video_device {int /*<<< orphan*/  entity; } ;
struct camss_video {TYPE_1__* camss; int /*<<< orphan*/  lock; int /*<<< orphan*/  q_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camss_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct camss_video* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void msm_video_release(struct video_device *vdev)
{
	struct camss_video *video = video_get_drvdata(vdev);

	media_entity_cleanup(&vdev->entity);

	mutex_destroy(&video->q_lock);
	mutex_destroy(&video->lock);

	if (atomic_dec_and_test(&video->camss->ref_count))
		camss_delete(video->camss);
}