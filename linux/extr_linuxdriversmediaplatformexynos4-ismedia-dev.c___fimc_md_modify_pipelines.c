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
struct media_graph {int dummy; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int __fimc_md_modify_pipeline (struct media_entity*,int) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_video_device (struct media_entity*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 

__attribute__((used)) static int __fimc_md_modify_pipelines(struct media_entity *entity, bool enable,
				      struct media_graph *graph)
{
	struct media_entity *entity_err = entity;
	int ret;

	/*
	 * Walk current graph and call the pipeline open/close routine for each
	 * opened video node that belongs to the graph of entities connected
	 * through active links. This is needed as we cannot power on/off the
	 * subdevs in random order.
	 */
	media_graph_walk_start(graph, entity);

	while ((entity = media_graph_walk_next(graph))) {
		if (!is_media_entity_v4l2_video_device(entity))
			continue;

		ret  = __fimc_md_modify_pipeline(entity, enable);

		if (ret < 0)
			goto err;
	}

	return 0;

err:
	media_graph_walk_start(graph, entity_err);

	while ((entity_err = media_graph_walk_next(graph))) {
		if (!is_media_entity_v4l2_video_device(entity_err))
			continue;

		__fimc_md_modify_pipeline(entity_err, !enable);

		if (entity_err == entity)
			break;
	}

	return ret;
}