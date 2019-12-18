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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  code; } ;
struct media_pad {int /*<<< orphan*/  entity; } ;
struct isp_pipeline {int /*<<< orphan*/  external; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  format; int /*<<< orphan*/  crc; int /*<<< orphan*/  data_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct isp_ccp2_device {TYPE_4__ if_cfg; struct v4l2_mbus_framefmt* formats; int /*<<< orphan*/ * pads; TYPE_1__ subdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  crc; scalar_t__ vpclk_div; } ;
struct TYPE_6__ {TYPE_3__ ccp2; } ;
struct isp_bus_cfg {TYPE_2__ bus; } ;

/* Variables and functions */
 size_t CCP2_PAD_SINK ; 
 int /*<<< orphan*/  ccp2_lcx_config (struct isp_ccp2_device*,TYPE_4__*) ; 
 int ccp2_phyif_config (struct isp_ccp2_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  ccp2_pwr_cfg (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  ccp2_vp_config (struct isp_ccp2_device*,scalar_t__) ; 
 int /*<<< orphan*/  g_skip_top_lines ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct isp_bus_cfg* v4l2_subdev_to_bus_cfg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp2_if_configure(struct isp_ccp2_device *ccp2)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	const struct isp_bus_cfg *buscfg;
	struct v4l2_mbus_framefmt *format;
	struct media_pad *pad;
	struct v4l2_subdev *sensor;
	u32 lines = 0;
	int ret;

	ccp2_pwr_cfg(ccp2);

	pad = media_entity_remote_pad(&ccp2->pads[CCP2_PAD_SINK]);
	sensor = media_entity_to_v4l2_subdev(pad->entity);
	buscfg = v4l2_subdev_to_bus_cfg(pipe->external);

	ret = ccp2_phyif_config(ccp2, &buscfg->bus.ccp2);
	if (ret < 0)
		return ret;

	ccp2_vp_config(ccp2, buscfg->bus.ccp2.vpclk_div + 1);

	v4l2_subdev_call(sensor, sensor, g_skip_top_lines, &lines);

	format = &ccp2->formats[CCP2_PAD_SINK];

	ccp2->if_cfg.data_start = lines;
	ccp2->if_cfg.crc = buscfg->bus.ccp2.crc;
	ccp2->if_cfg.format = format->code;
	ccp2->if_cfg.data_size = format->height;

	ccp2_lcx_config(ccp2, &ccp2->if_cfg);

	return 0;
}