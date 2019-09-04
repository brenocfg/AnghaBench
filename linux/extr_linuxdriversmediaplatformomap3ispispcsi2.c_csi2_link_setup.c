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
struct isp_csi2_ctrl_cfg {int vp_only_enable; int vp_clk_enable; } ;
struct isp_csi2_device {int output; struct isp_csi2_ctrl_cfg ctrl; } ;

/* Variables and functions */
 int CSI2_OUTPUT_CCDC ; 
 int CSI2_OUTPUT_MEMORY ; 
#define  CSI2_PAD_SOURCE 128 
 int EBUSY ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 scalar_t__ is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct isp_csi2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2_link_setup(struct media_entity *entity,
			   const struct media_pad *local,
			   const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	struct isp_csi2_ctrl_cfg *ctrl = &csi2->ctrl;
	unsigned int index = local->index;

	/*
	 * The ISP core doesn't support pipelines with multiple video outputs.
	 * Revisit this when it will be implemented, and return -EBUSY for now.
	 */

	/* FIXME: this is actually a hack! */
	if (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	switch (index) {
	case CSI2_PAD_SOURCE:
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (csi2->output & ~CSI2_OUTPUT_MEMORY)
				return -EBUSY;
			csi2->output |= CSI2_OUTPUT_MEMORY;
		} else {
			csi2->output &= ~CSI2_OUTPUT_MEMORY;
		}
		break;

	case CSI2_PAD_SOURCE | 2 << 16:
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (csi2->output & ~CSI2_OUTPUT_CCDC)
				return -EBUSY;
			csi2->output |= CSI2_OUTPUT_CCDC;
		} else {
			csi2->output &= ~CSI2_OUTPUT_CCDC;
		}
		break;

	default:
		/* Link from camera to CSI2 is fixed... */
		return -EINVAL;
	}

	ctrl->vp_only_enable =
		(csi2->output & CSI2_OUTPUT_MEMORY) ? false : true;
	ctrl->vp_clk_enable = !!(csi2->output & CSI2_OUTPUT_CCDC);

	return 0;
}