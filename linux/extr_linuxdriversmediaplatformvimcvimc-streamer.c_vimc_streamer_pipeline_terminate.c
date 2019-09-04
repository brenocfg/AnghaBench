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
struct vimc_stream {int pipe_size; TYPE_1__** ved_pipeline; } ;
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;
struct TYPE_2__ {struct media_entity* ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct media_entity* vimc_get_source_entity (struct media_entity*) ; 

__attribute__((used)) static void vimc_streamer_pipeline_terminate(struct vimc_stream *stream)
{
	struct media_entity *entity;
	struct v4l2_subdev *sd;

	while (stream->pipe_size) {
		stream->pipe_size--;
		entity = stream->ved_pipeline[stream->pipe_size]->ent;
		entity = vimc_get_source_entity(entity);
		stream->ved_pipeline[stream->pipe_size] = NULL;

		if (!is_media_entity_v4l2_subdev(entity))
			continue;

		sd = media_entity_to_v4l2_subdev(entity);
		v4l2_subdev_call(sd, video, s_stream, 0);
	}
}