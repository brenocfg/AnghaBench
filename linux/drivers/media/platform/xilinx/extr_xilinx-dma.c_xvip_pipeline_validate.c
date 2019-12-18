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
struct xvip_pipeline {unsigned int num_dmas; struct xvip_dma* output; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {struct media_device* mdev; } ;
struct media_entity {scalar_t__ function; TYPE_2__ graph_obj; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct xvip_dma {TYPE_3__ pad; TYPE_1__ video; } ;
struct media_graph {int dummy; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 int EPIPE ; 
 scalar_t__ MEDIA_ENT_F_IO_V4L ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  media_entity_to_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 int media_graph_walk_init (struct media_graph*,struct media_device*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xvip_dma* to_xvip_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xvip_pipeline_validate(struct xvip_pipeline *pipe,
				  struct xvip_dma *start)
{
	struct media_graph graph;
	struct media_entity *entity = &start->video.entity;
	struct media_device *mdev = entity->graph_obj.mdev;
	unsigned int num_inputs = 0;
	unsigned int num_outputs = 0;
	int ret;

	mutex_lock(&mdev->graph_mutex);

	/* Walk the graph to locate the video nodes. */
	ret = media_graph_walk_init(&graph, mdev);
	if (ret) {
		mutex_unlock(&mdev->graph_mutex);
		return ret;
	}

	media_graph_walk_start(&graph, entity);

	while ((entity = media_graph_walk_next(&graph))) {
		struct xvip_dma *dma;

		if (entity->function != MEDIA_ENT_F_IO_V4L)
			continue;

		dma = to_xvip_dma(media_entity_to_video_device(entity));

		if (dma->pad.flags & MEDIA_PAD_FL_SINK) {
			pipe->output = dma;
			num_outputs++;
		} else {
			num_inputs++;
		}
	}

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	/* We need exactly one output and zero or one input. */
	if (num_outputs != 1 || num_inputs > 1)
		return -EPIPE;

	pipe->num_dmas = num_inputs + num_outputs;

	return 0;
}