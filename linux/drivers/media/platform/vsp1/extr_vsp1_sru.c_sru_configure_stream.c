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
typedef  int u32 ;
struct vsp1_sru_param {int ctrl0; int ctrl2; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct vsp1_sru {int intensity; TYPE_1__ entity; } ;
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; scalar_t__ width; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_ARGB8888_1X32 ; 
 int /*<<< orphan*/  SRU_PAD_SINK ; 
 int /*<<< orphan*/  SRU_PAD_SOURCE ; 
 int /*<<< orphan*/  VI6_SRU_CTRL0 ; 
 int VI6_SRU_CTRL0_MODE_UPSCALE ; 
 int VI6_SRU_CTRL0_PARAM2 ; 
 int VI6_SRU_CTRL0_PARAM3 ; 
 int VI6_SRU_CTRL0_PARAM4 ; 
 int /*<<< orphan*/  VI6_SRU_CTRL1 ; 
 int VI6_SRU_CTRL1_PARAM5 ; 
 int /*<<< orphan*/  VI6_SRU_CTRL2 ; 
 struct vsp1_sru* to_sru (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vsp1_sru_param* vsp1_sru_params ; 
 int /*<<< orphan*/  vsp1_sru_write (struct vsp1_sru*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sru_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	const struct vsp1_sru_param *param;
	struct vsp1_sru *sru = to_sru(&entity->subdev);
	struct v4l2_mbus_framefmt *input;
	struct v4l2_mbus_framefmt *output;
	u32 ctrl0;

	input = vsp1_entity_get_pad_format(&sru->entity, sru->entity.config,
					   SRU_PAD_SINK);
	output = vsp1_entity_get_pad_format(&sru->entity, sru->entity.config,
					    SRU_PAD_SOURCE);

	if (input->code == MEDIA_BUS_FMT_ARGB8888_1X32)
		ctrl0 = VI6_SRU_CTRL0_PARAM2 | VI6_SRU_CTRL0_PARAM3
		      | VI6_SRU_CTRL0_PARAM4;
	else
		ctrl0 = VI6_SRU_CTRL0_PARAM3;

	if (input->width != output->width)
		ctrl0 |= VI6_SRU_CTRL0_MODE_UPSCALE;

	param = &vsp1_sru_params[sru->intensity - 1];

	ctrl0 |= param->ctrl0;

	vsp1_sru_write(sru, dlb, VI6_SRU_CTRL0, ctrl0);
	vsp1_sru_write(sru, dlb, VI6_SRU_CTRL1, VI6_SRU_CTRL1_PARAM5);
	vsp1_sru_write(sru, dlb, VI6_SRU_CTRL2, param->ctrl2);
}