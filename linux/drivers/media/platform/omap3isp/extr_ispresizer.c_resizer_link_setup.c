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
struct isp_res_device {void* input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 void* RESIZER_INPUT_MEMORY ; 
 void* RESIZER_INPUT_NONE ; 
 void* RESIZER_INPUT_VP ; 
#define  RESZ_PAD_SINK 129 
#define  RESZ_PAD_SOURCE 128 
 scalar_t__ is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct isp_res_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_link_setup(struct media_entity *entity,
			      const struct media_pad *local,
			      const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct isp_res_device *res = v4l2_get_subdevdata(sd);
	unsigned int index = local->index;

	/* FIXME: this is actually a hack! */
	if (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	switch (index) {
	case RESZ_PAD_SINK:
		/* read from memory */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (res->input == RESIZER_INPUT_VP)
				return -EBUSY;
			res->input = RESIZER_INPUT_MEMORY;
		} else {
			if (res->input == RESIZER_INPUT_MEMORY)
				res->input = RESIZER_INPUT_NONE;
		}
		break;

	case RESZ_PAD_SINK | 2 << 16:
		/* read from ccdc or previewer */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (res->input == RESIZER_INPUT_MEMORY)
				return -EBUSY;
			res->input = RESIZER_INPUT_VP;
		} else {
			if (res->input == RESIZER_INPUT_VP)
				res->input = RESIZER_INPUT_NONE;
		}
		break;

	case RESZ_PAD_SOURCE:
		/* resizer always write to memory */
		break;

	default:
		return -EINVAL;
	}

	return 0;
}