#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vsp1_pipeline {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct vsp1_lif {TYPE_2__ entity; } ;
struct vsp1_entity {TYPE_1__* vsp1; int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_mbus_framefmt {int height; scalar_t__ code; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIF_PAD_SOURCE ; 
 int const VI6_IP_VERSION_MASK ; 
 int VI6_IP_VERSION_MODEL_MASK ; 
#define  VI6_IP_VERSION_MODEL_VSPDL_GEN3 132 
#define  VI6_IP_VERSION_MODEL_VSPD_GEN2 131 
#define  VI6_IP_VERSION_MODEL_VSPD_GEN3 130 
#define  VI6_IP_VERSION_MODEL_VSPD_V2H 129 
#define  VI6_IP_VERSION_MODEL_VSPD_V3 128 
 int const VI6_IP_VERSION_SOC_V3M ; 
 int /*<<< orphan*/  VI6_LIF_CSBTH ; 
 unsigned int VI6_LIF_CSBTH_HBTH_SHIFT ; 
 unsigned int VI6_LIF_CSBTH_LBTH_SHIFT ; 
 int /*<<< orphan*/  VI6_LIF_CTRL ; 
 unsigned int VI6_LIF_CTRL_CFMT ; 
 unsigned int VI6_LIF_CTRL_LIF_EN ; 
 unsigned int VI6_LIF_CTRL_OBTH_SHIFT ; 
 unsigned int VI6_LIF_CTRL_REQSEL ; 
 int /*<<< orphan*/  VI6_LIF_LBA ; 
 int VI6_LIF_LBA_LBA0 ; 
 int VI6_LIF_LBA_LBA1_SHIFT ; 
 unsigned int min (unsigned int,int) ; 
 struct vsp1_lif* to_lif (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_lif_write (struct vsp1_lif*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lif_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	const struct v4l2_mbus_framefmt *format;
	struct vsp1_lif *lif = to_lif(&entity->subdev);
	unsigned int hbth;
	unsigned int obth;
	unsigned int lbth;

	format = vsp1_entity_get_pad_format(&lif->entity, lif->entity.config,
					    LIF_PAD_SOURCE);

	switch (entity->vsp1->version & VI6_IP_VERSION_MODEL_MASK) {
	case VI6_IP_VERSION_MODEL_VSPD_GEN2:
	case VI6_IP_VERSION_MODEL_VSPD_V2H:
		hbth = 1536;
		obth = min(128U, (format->width + 1) / 2 * format->height - 4);
		lbth = 1520;
		break;

	case VI6_IP_VERSION_MODEL_VSPDL_GEN3:
	case VI6_IP_VERSION_MODEL_VSPD_V3:
		hbth = 0;
		obth = 1500;
		lbth = 0;
		break;

	case VI6_IP_VERSION_MODEL_VSPD_GEN3:
	default:
		hbth = 0;
		obth = 3000;
		lbth = 0;
		break;
	}

	vsp1_lif_write(lif, dlb, VI6_LIF_CSBTH,
			(hbth << VI6_LIF_CSBTH_HBTH_SHIFT) |
			(lbth << VI6_LIF_CSBTH_LBTH_SHIFT));

	vsp1_lif_write(lif, dlb, VI6_LIF_CTRL,
			(obth << VI6_LIF_CTRL_OBTH_SHIFT) |
			(format->code == 0 ? VI6_LIF_CTRL_CFMT : 0) |
			VI6_LIF_CTRL_REQSEL | VI6_LIF_CTRL_LIF_EN);

	/*
	 * On R-Car V3M the LIF0 buffer attribute register has to be set to a
	 * non-default value to guarantee proper operation (otherwise artifacts
	 * may appear on the output). The value required by the manual is not
	 * explained but is likely a buffer size or threshold.
	 */
	if ((entity->vsp1->version & VI6_IP_VERSION_MASK) ==
	    (VI6_IP_VERSION_MODEL_VSPD_V3 | VI6_IP_VERSION_SOC_V3M))
		vsp1_lif_write(lif, dlb, VI6_LIF_LBA,
			       VI6_LIF_LBA_LBA0 |
			       (1536 << VI6_LIF_LBA_LBA1_SHIFT));
}