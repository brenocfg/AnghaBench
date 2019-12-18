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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct imx7_csi {int /*<<< orphan*/  vdev; TYPE_2__* pad; TYPE_1__* frame_interval; int /*<<< orphan*/ * cc; int /*<<< orphan*/ * format_mbus; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int numerator; int denominator; } ;

/* Variables and functions */
 int IMX7_CSI_PADS_NUM ; 
 int IMX7_CSI_PAD_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int imx_media_capture_device_register (int /*<<< orphan*/ ) ; 
 int imx_media_init_mbus_fmt (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx7_csi_registered(struct v4l2_subdev *sd)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	int ret;
	int i;

	for (i = 0; i < IMX7_CSI_PADS_NUM; i++) {
		csi->pad[i].flags = (i == IMX7_CSI_PAD_SINK) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

		/* set a default mbus format  */
		ret = imx_media_init_mbus_fmt(&csi->format_mbus[i],
					      800, 600, 0, V4L2_FIELD_NONE,
					      &csi->cc[i]);
		if (ret < 0)
			return ret;

		/* init default frame interval */
		csi->frame_interval[i].numerator = 1;
		csi->frame_interval[i].denominator = 30;
	}

	ret = media_entity_pads_init(&sd->entity, IMX7_CSI_PADS_NUM, csi->pad);
	if (ret < 0)
		return ret;

	return imx_media_capture_device_register(csi->vdev);
}