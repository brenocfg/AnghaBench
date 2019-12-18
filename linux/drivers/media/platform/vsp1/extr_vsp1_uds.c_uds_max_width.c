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
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct vsp1_uds {TYPE_1__ entity; } ;
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct v4l2_mbus_framefmt {unsigned int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDS_PAD_SINK ; 
 int /*<<< orphan*/  UDS_PAD_SOURCE ; 
 struct vsp1_uds* to_uds (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int uds_max_width(struct vsp1_entity *entity,
				  struct vsp1_pipeline *pipe)
{
	struct vsp1_uds *uds = to_uds(&entity->subdev);
	const struct v4l2_mbus_framefmt *output;
	const struct v4l2_mbus_framefmt *input;
	unsigned int hscale;

	input = vsp1_entity_get_pad_format(&uds->entity, uds->entity.config,
					   UDS_PAD_SINK);
	output = vsp1_entity_get_pad_format(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);
	hscale = output->width / input->width;

	/*
	 * The maximum width of the UDS is 304 pixels. These are input pixels
	 * in the event of up-scaling, and output pixels in the event of
	 * downscaling.
	 *
	 * To support overlapping partition windows we clamp at units of 256 and
	 * the remaining pixels are reserved.
	 */
	if (hscale <= 2)
		return 256;
	else if (hscale <= 4)
		return 512;
	else if (hscale <= 8)
		return 1024;
	else
		return 2048;
}