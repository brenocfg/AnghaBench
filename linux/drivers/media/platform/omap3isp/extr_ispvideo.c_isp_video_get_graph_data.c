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
struct media_graph {int dummy; } ;
struct TYPE_3__ {struct media_device* mdev; } ;
struct media_entity {TYPE_1__ graph_obj; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct isp_video {scalar_t__ type; TYPE_2__ video; } ;
struct isp_pipeline {struct isp_video* output; struct isp_video* input; int /*<<< orphan*/  ent_enum; } ;

/* Variables and functions */
 int EPIPE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  is_media_entity_v4l2_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_to_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 int media_graph_walk_init (struct media_graph*,struct media_device*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video* to_isp_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp_video_get_graph_data(struct isp_video *video,
				    struct isp_pipeline *pipe)
{
	struct media_graph graph;
	struct media_entity *entity = &video->video.entity;
	struct media_device *mdev = entity->graph_obj.mdev;
	struct isp_video *far_end = NULL;
	int ret;

	mutex_lock(&mdev->graph_mutex);
	ret = media_graph_walk_init(&graph, mdev);
	if (ret) {
		mutex_unlock(&mdev->graph_mutex);
		return ret;
	}

	media_graph_walk_start(&graph, entity);

	while ((entity = media_graph_walk_next(&graph))) {
		struct isp_video *__video;

		media_entity_enum_set(&pipe->ent_enum, entity);

		if (far_end != NULL)
			continue;

		if (entity == &video->video.entity)
			continue;

		if (!is_media_entity_v4l2_video_device(entity))
			continue;

		__video = to_isp_video(media_entity_to_video_device(entity));
		if (__video->type != video->type)
			far_end = __video;
	}

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		pipe->input = far_end;
		pipe->output = video;
	} else {
		if (far_end == NULL)
			return -EPIPE;

		pipe->input = video;
		pipe->output = far_end;
	}

	return 0;
}