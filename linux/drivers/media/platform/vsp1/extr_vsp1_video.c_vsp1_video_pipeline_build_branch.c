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
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct vsp1_entity {scalar_t__ type; size_t source_pad; struct media_pad* pads; TYPE_3__ subdev; TYPE_1__* vsp1; } ;
struct vsp1_rwpf {size_t brx_input; struct vsp1_entity entity; } ;
struct vsp1_pipeline {struct vsp1_entity* uds_input; struct vsp1_entity* uds; } ;
struct vsp1_brx {struct vsp1_entity entity; TYPE_2__* inputs; } ;
struct media_pad {size_t index; int /*<<< orphan*/  entity; } ;
struct media_entity_enum {int dummy; } ;
struct TYPE_5__ {struct vsp1_rwpf* rpf; } ;
struct TYPE_4__ {int /*<<< orphan*/  media_dev; } ;

/* Variables and functions */
 int EPIPE ; 
 size_t RWPF_PAD_SOURCE ; 
 scalar_t__ VSP1_ENTITY_BRS ; 
 scalar_t__ VSP1_ENTITY_BRU ; 
 scalar_t__ VSP1_ENTITY_UDS ; 
 scalar_t__ VSP1_ENTITY_WPF ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (struct media_entity_enum*) ; 
 int media_entity_enum_init (struct media_entity_enum*,int /*<<< orphan*/ *) ; 
 scalar_t__ media_entity_enum_test_and_set (struct media_entity_enum*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct vsp1_brx* to_brx (TYPE_3__*) ; 
 struct vsp1_entity* to_vsp1_entity (int /*<<< orphan*/ ) ; 
 struct media_pad* vsp1_entity_remote_pad (struct media_pad*) ; 

__attribute__((used)) static int vsp1_video_pipeline_build_branch(struct vsp1_pipeline *pipe,
					    struct vsp1_rwpf *input,
					    struct vsp1_rwpf *output)
{
	struct media_entity_enum ent_enum;
	struct vsp1_entity *entity;
	struct media_pad *pad;
	struct vsp1_brx *brx = NULL;
	int ret;

	ret = media_entity_enum_init(&ent_enum, &input->entity.vsp1->media_dev);
	if (ret < 0)
		return ret;

	/*
	 * The main data path doesn't include the HGO or HGT, use
	 * vsp1_entity_remote_pad() to traverse the graph.
	 */

	pad = vsp1_entity_remote_pad(&input->entity.pads[RWPF_PAD_SOURCE]);

	while (1) {
		if (pad == NULL) {
			ret = -EPIPE;
			goto out;
		}

		/* We've reached a video node, that shouldn't have happened. */
		if (!is_media_entity_v4l2_subdev(pad->entity)) {
			ret = -EPIPE;
			goto out;
		}

		entity = to_vsp1_entity(
			media_entity_to_v4l2_subdev(pad->entity));

		/*
		 * A BRU or BRS is present in the pipeline, store its input pad
		 * number in the input RPF for use when configuring the RPF.
		 */
		if (entity->type == VSP1_ENTITY_BRU ||
		    entity->type == VSP1_ENTITY_BRS) {
			/* BRU and BRS can't be chained. */
			if (brx) {
				ret = -EPIPE;
				goto out;
			}

			brx = to_brx(&entity->subdev);
			brx->inputs[pad->index].rpf = input;
			input->brx_input = pad->index;
		}

		/* We've reached the WPF, we're done. */
		if (entity->type == VSP1_ENTITY_WPF)
			break;

		/* Ensure the branch has no loop. */
		if (media_entity_enum_test_and_set(&ent_enum,
						   &entity->subdev.entity)) {
			ret = -EPIPE;
			goto out;
		}

		/* UDS can't be chained. */
		if (entity->type == VSP1_ENTITY_UDS) {
			if (pipe->uds) {
				ret = -EPIPE;
				goto out;
			}

			pipe->uds = entity;
			pipe->uds_input = brx ? &brx->entity : &input->entity;
		}

		/* Follow the source link, ignoring any HGO or HGT. */
		pad = &entity->pads[entity->source_pad];
		pad = vsp1_entity_remote_pad(pad);
	}

	/* The last entity must be the output WPF. */
	if (entity != &output->entity)
		ret = -EPIPE;

out:
	media_entity_enum_cleanup(&ent_enum);

	return ret;
}