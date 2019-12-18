#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vsp1_pipeline {int /*<<< orphan*/  kref; TYPE_3__* output; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_5__ {TYPE_1__* vsp1; } ;
struct TYPE_6__ {TYPE_2__ entity; } ;
struct TYPE_4__ {struct media_device media_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_release ; 

__attribute__((used)) static void vsp1_video_pipeline_put(struct vsp1_pipeline *pipe)
{
	struct media_device *mdev = &pipe->output->entity.vsp1->media_dev;

	mutex_lock(&mdev->graph_mutex);
	kref_put(&pipe->kref, vsp1_video_pipeline_release);
	mutex_unlock(&mdev->graph_mutex);
}