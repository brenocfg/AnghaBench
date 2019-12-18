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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct ipu_csi {int dummy; } ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_6__ {int width; int height; } ;
struct csi_priv {struct ipu_csi* csi; struct ipu_csi* fim; int /*<<< orphan*/  vdev; TYPE_4__* pad; int /*<<< orphan*/  sd; TYPE_3__ compose; TYPE_2__ crop; int /*<<< orphan*/ * skip; TYPE_1__* frame_interval; int /*<<< orphan*/ * cc; int /*<<< orphan*/ * format_mbus; int /*<<< orphan*/  csi_id; int /*<<< orphan*/  ipu; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int numerator; int denominator; } ;

/* Variables and functions */
 int CSI_NUM_PADS ; 
 int CSI_SINK_PAD ; 
 int /*<<< orphan*/  CS_SEL_YUV ; 
 scalar_t__ IS_ERR (struct ipu_csi*) ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PTR_ERR (struct ipu_csi*) ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/ * csi_skip ; 
 int imx_media_capture_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_enum_ipu_format (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_fim_free (struct ipu_csi*) ; 
 struct ipu_csi* imx_media_fim_init (int /*<<< orphan*/ *) ; 
 int imx_media_init_mbus_fmt (int /*<<< orphan*/ *,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ipu_csi* ipu_csi_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_put (struct ipu_csi*) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_registered(struct v4l2_subdev *sd)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct ipu_csi *csi;
	int i, ret;
	u32 code;

	/* get handle to IPU CSI */
	csi = ipu_csi_get(priv->ipu, priv->csi_id);
	if (IS_ERR(csi)) {
		v4l2_err(&priv->sd, "failed to get CSI%d\n", priv->csi_id);
		return PTR_ERR(csi);
	}
	priv->csi = csi;

	for (i = 0; i < CSI_NUM_PADS; i++) {
		priv->pad[i].flags = (i == CSI_SINK_PAD) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

		code = 0;
		if (i != CSI_SINK_PAD)
			imx_media_enum_ipu_format(&code, 0, CS_SEL_YUV);

		/* set a default mbus format  */
		ret = imx_media_init_mbus_fmt(&priv->format_mbus[i],
					      640, 480, code, V4L2_FIELD_NONE,
					      &priv->cc[i]);
		if (ret)
			goto put_csi;

		/* init default frame interval */
		priv->frame_interval[i].numerator = 1;
		priv->frame_interval[i].denominator = 30;
	}

	/* disable frame skipping */
	priv->skip = &csi_skip[0];

	/* init default crop and compose rectangle sizes */
	priv->crop.width = 640;
	priv->crop.height = 480;
	priv->compose.width = 640;
	priv->compose.height = 480;

	priv->fim = imx_media_fim_init(&priv->sd);
	if (IS_ERR(priv->fim)) {
		ret = PTR_ERR(priv->fim);
		goto put_csi;
	}

	ret = media_entity_pads_init(&sd->entity, CSI_NUM_PADS, priv->pad);
	if (ret)
		goto free_fim;

	ret = imx_media_capture_device_register(priv->vdev);
	if (ret)
		goto free_fim;

	return 0;

free_fim:
	if (priv->fim)
		imx_media_fim_free(priv->fim);
put_csi:
	ipu_csi_put(priv->csi);
	return ret;
}