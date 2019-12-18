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
struct vimc_stream {int pipe_size; struct vimc_ent_device** ved_pipeline; } ;
struct vimc_ent_device {int /*<<< orphan*/  ent; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void vimc_streamer_pipeline_terminate(struct vimc_stream *stream)
{
	struct vimc_ent_device *ved;
	struct v4l2_subdev *sd;

	while (stream->pipe_size) {
		stream->pipe_size--;
		ved = stream->ved_pipeline[stream->pipe_size];
		stream->ved_pipeline[stream->pipe_size] = NULL;

		if (!is_media_entity_v4l2_subdev(ved->ent))
			continue;

		sd = media_entity_to_v4l2_subdev(ved->ent);
		v4l2_subdev_call(sd, video, s_stream, 0);
	}
}