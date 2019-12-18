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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct vsp1_clu {int yuv_mode; TYPE_1__ entity; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLU_PAD_SINK ; 
 scalar_t__ MEDIA_BUS_FMT_AYUV8_1X32 ; 
 struct vsp1_clu* to_clu (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clu_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	struct vsp1_clu *clu = to_clu(&entity->subdev);
	struct v4l2_mbus_framefmt *format;

	/*
	 * The yuv_mode can't be changed during streaming. Cache it internally
	 * for future runtime configuration calls.
	 */
	format = vsp1_entity_get_pad_format(&clu->entity,
					    clu->entity.config,
					    CLU_PAD_SINK);
	clu->yuv_mode = format->code == MEDIA_BUS_FMT_AYUV8_1X32;
}