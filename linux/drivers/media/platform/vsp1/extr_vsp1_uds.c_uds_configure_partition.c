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
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct vsp1_uds {TYPE_3__ entity; } ;
struct vsp1_pipeline {struct vsp1_partition* partition; } ;
struct TYPE_5__ {int width; } ;
struct TYPE_4__ {int width; } ;
struct vsp1_partition {TYPE_2__ uds_source; TYPE_1__ uds_sink; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_mbus_framefmt {int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDS_PAD_SOURCE ; 
 int /*<<< orphan*/  VI6_UDS_CLIP_SIZE ; 
 int VI6_UDS_CLIP_SIZE_HSIZE_SHIFT ; 
 int VI6_UDS_CLIP_SIZE_VSIZE_SHIFT ; 
 int /*<<< orphan*/  VI6_UDS_HSZCLIP ; 
 int VI6_UDS_HSZCLIP_HCEN ; 
 int VI6_UDS_HSZCLIP_HCL_OFST_SHIFT ; 
 int VI6_UDS_HSZCLIP_HCL_SIZE_SHIFT ; 
 struct vsp1_uds* to_uds (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_uds_write (struct vsp1_uds*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uds_configure_partition(struct vsp1_entity *entity,
				    struct vsp1_pipeline *pipe,
				    struct vsp1_dl_list *dl,
				    struct vsp1_dl_body *dlb)
{
	struct vsp1_uds *uds = to_uds(&entity->subdev);
	struct vsp1_partition *partition = pipe->partition;
	const struct v4l2_mbus_framefmt *output;

	output = vsp1_entity_get_pad_format(&uds->entity, uds->entity.config,
					    UDS_PAD_SOURCE);

	/* Input size clipping. */
	vsp1_uds_write(uds, dlb, VI6_UDS_HSZCLIP, VI6_UDS_HSZCLIP_HCEN |
		       (0 << VI6_UDS_HSZCLIP_HCL_OFST_SHIFT) |
		       (partition->uds_sink.width
				<< VI6_UDS_HSZCLIP_HCL_SIZE_SHIFT));

	/* Output size clipping. */
	vsp1_uds_write(uds, dlb, VI6_UDS_CLIP_SIZE,
		       (partition->uds_source.width
				<< VI6_UDS_CLIP_SIZE_HSIZE_SHIFT) |
		       (output->height
				<< VI6_UDS_CLIP_SIZE_VSIZE_SHIFT));
}