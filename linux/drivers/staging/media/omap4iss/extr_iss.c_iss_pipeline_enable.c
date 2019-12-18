#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {struct media_pad* pads; } ;
struct iss_pipeline {int state; int do_propagation; TYPE_4__* output; int /*<<< orphan*/  lock; int /*<<< orphan*/  ent_enum; } ;
struct TYPE_7__ {struct v4l2_subdev subdev; } ;
struct TYPE_6__ {struct v4l2_subdev subdev; } ;
struct iss_device {TYPE_3__ csi2b; TYPE_2__ csi2a; int /*<<< orphan*/  crashed; } ;
typedef  enum iss_pipeline_stream_state { ____Placeholder_iss_pipeline_stream_state } iss_pipeline_stream_state ;
struct TYPE_5__ {struct media_entity entity; } ;
struct TYPE_8__ {struct iss_device* iss; TYPE_1__ video; } ;

/* Variables and functions */
 int EIO ; 
 int ENOIOCTLCMD ; 
 int ISS_PIPELINE_IDLE_INPUT ; 
 int ISS_PIPELINE_IDLE_OUTPUT ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  iss_pipeline_disable (struct iss_pipeline*,struct media_entity*) ; 
 int /*<<< orphan*/  iss_print_status (struct iss_device*) ; 
 scalar_t__ media_entity_enum_intersects (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int iss_pipeline_enable(struct iss_pipeline *pipe,
			       enum iss_pipeline_stream_state mode)
{
	struct iss_device *iss = pipe->output->iss;
	struct media_entity *entity;
	struct media_pad *pad;
	struct v4l2_subdev *subdev;
	unsigned long flags;
	int ret;

	/* If one of the entities in the pipeline has crashed it will not work
	 * properly. Refuse to start streaming in that case. This check must be
	 * performed before the loop below to avoid starting entities if the
	 * pipeline won't start anyway (those entities would then likely fail to
	 * stop, making the problem worse).
	 */
	if (media_entity_enum_intersects(&pipe->ent_enum, &iss->crashed))
		return -EIO;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~(ISS_PIPELINE_IDLE_INPUT | ISS_PIPELINE_IDLE_OUTPUT);
	spin_unlock_irqrestore(&pipe->lock, flags);

	pipe->do_propagation = false;

	entity = &pipe->output->video.entity;
	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, mode);
		if (ret < 0 && ret != -ENOIOCTLCMD) {
			iss_pipeline_disable(pipe, entity);
			return ret;
		}

		if (subdev == &iss->csi2a.subdev ||
		    subdev == &iss->csi2b.subdev)
			pipe->do_propagation = true;
	}

	iss_print_status(pipe->output->iss);
	return 0;
}