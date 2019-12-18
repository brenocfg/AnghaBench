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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct TYPE_3__ {int numerator; int denominator; } ;
struct prp_priv {int /*<<< orphan*/  vdev; TYPE_2__* pad; TYPE_1__ frame_interval; int /*<<< orphan*/ * cc; int /*<<< orphan*/ * format_mbus; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_YUV ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PRPENCVF_NUM_PADS ; 
 int PRPENCVF_SINK_PAD ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int imx_media_capture_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_enum_ipu_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx_media_init_mbus_fmt (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int prp_init_controls (struct prp_priv*) ; 
 struct prp_priv* sd_to_priv (struct v4l2_subdev*) ; 

__attribute__((used)) static int prp_registered(struct v4l2_subdev *sd)
{
	struct prp_priv *priv = sd_to_priv(sd);
	int i, ret;
	u32 code;

	for (i = 0; i < PRPENCVF_NUM_PADS; i++) {
		priv->pad[i].flags = (i == PRPENCVF_SINK_PAD) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

		/* set a default mbus format  */
		imx_media_enum_ipu_format(&code, 0, CS_SEL_YUV);
		ret = imx_media_init_mbus_fmt(&priv->format_mbus[i],
					      640, 480, code, V4L2_FIELD_NONE,
					      &priv->cc[i]);
		if (ret)
			return ret;
	}

	/* init default frame interval */
	priv->frame_interval.numerator = 1;
	priv->frame_interval.denominator = 30;

	ret = media_entity_pads_init(&sd->entity, PRPENCVF_NUM_PADS,
				     priv->pad);
	if (ret)
		return ret;

	ret = imx_media_capture_device_register(priv->vdev);
	if (ret)
		return ret;

	ret = prp_init_controls(priv);
	if (ret)
		goto unreg;

	return 0;
unreg:
	imx_media_capture_device_unregister(priv->vdev);
	return ret;
}