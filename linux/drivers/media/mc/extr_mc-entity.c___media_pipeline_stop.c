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
struct media_pipeline {int /*<<< orphan*/  streaming_count; struct media_graph graph; } ;
struct media_entity {scalar_t__ stream_count; struct media_pipeline* pipe; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 

void __media_pipeline_stop(struct media_entity *entity)
{
	struct media_graph *graph = &entity->pipe->graph;
	struct media_pipeline *pipe = entity->pipe;

	/*
	 * If the following check fails, the driver has performed an
	 * unbalanced call to media_pipeline_stop()
	 */
	if (WARN_ON(!pipe))
		return;

	media_graph_walk_start(graph, entity);

	while ((entity = media_graph_walk_next(graph))) {
		/* Sanity check for negative stream_count */
		if (!WARN_ON_ONCE(entity->stream_count <= 0)) {
			entity->stream_count--;
			if (entity->stream_count == 0)
				entity->pipe = NULL;
		}
	}

	if (!--pipe->streaming_count)
		media_graph_walk_cleanup(graph);

}