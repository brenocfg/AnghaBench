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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct media_pad {unsigned int index; int /*<<< orphan*/  entity; } ;
struct media_entity {int dummy; } ;
struct isp_prev_device {int output; void* input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 void* PREVIEW_INPUT_CCDC ; 
 void* PREVIEW_INPUT_MEMORY ; 
 void* PREVIEW_INPUT_NONE ; 
 int PREVIEW_OUTPUT_MEMORY ; 
 int PREVIEW_OUTPUT_RESIZER ; 
#define  PREV_PAD_SINK 129 
#define  PREV_PAD_SOURCE 128 
 scalar_t__ is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct isp_prev_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int preview_link_setup(struct media_entity *entity,
			      const struct media_pad *local,
			      const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct isp_prev_device *prev = v4l2_get_subdevdata(sd);
	unsigned int index = local->index;

	/* FIXME: this is actually a hack! */
	if (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	switch (index) {
	case PREV_PAD_SINK:
		/* read from memory */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (prev->input == PREVIEW_INPUT_CCDC)
				return -EBUSY;
			prev->input = PREVIEW_INPUT_MEMORY;
		} else {
			if (prev->input == PREVIEW_INPUT_MEMORY)
				prev->input = PREVIEW_INPUT_NONE;
		}
		break;

	case PREV_PAD_SINK | 2 << 16:
		/* read from ccdc */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (prev->input == PREVIEW_INPUT_MEMORY)
				return -EBUSY;
			prev->input = PREVIEW_INPUT_CCDC;
		} else {
			if (prev->input == PREVIEW_INPUT_CCDC)
				prev->input = PREVIEW_INPUT_NONE;
		}
		break;

	/*
	 * The ISP core doesn't support pipelines with multiple video outputs.
	 * Revisit this when it will be implemented, and return -EBUSY for now.
	 */

	case PREV_PAD_SOURCE:
		/* write to memory */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (prev->output & ~PREVIEW_OUTPUT_MEMORY)
				return -EBUSY;
			prev->output |= PREVIEW_OUTPUT_MEMORY;
		} else {
			prev->output &= ~PREVIEW_OUTPUT_MEMORY;
		}
		break;

	case PREV_PAD_SOURCE | 2 << 16:
		/* write to resizer */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (prev->output & ~PREVIEW_OUTPUT_RESIZER)
				return -EBUSY;
			prev->output |= PREVIEW_OUTPUT_RESIZER;
		} else {
			prev->output &= ~PREVIEW_OUTPUT_RESIZER;
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}