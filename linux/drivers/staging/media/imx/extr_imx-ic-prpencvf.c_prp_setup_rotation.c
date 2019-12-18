#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; } ;
struct prp_priv {TYPE_3__* rot_buf; int /*<<< orphan*/  ic; int /*<<< orphan*/  rot_out_ch; int /*<<< orphan*/  rot_in_ch; int /*<<< orphan*/  out_ch; int /*<<< orphan*/  rot_mode; struct imx_media_pixfmt** cc; struct v4l2_mbus_framefmt* format_mbus; struct imx_ic_priv* ic_priv; struct imx_media_video_dev* vdev; } ;
struct ipu_ic_csc {int dummy; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct TYPE_6__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {struct imx_media_pixfmt* cc; TYPE_2__ fmt; } ;
struct imx_media_pixfmt {int /*<<< orphan*/  cs; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu_dev; int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_ROTATE_NONE ; 
 size_t PRPENCVF_SINK_PAD ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int imx_media_alloc_dma_buf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ipu_ic_calc_csc (struct ipu_ic_csc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_task_enable (int /*<<< orphan*/ ) ; 
 int ipu_ic_task_init (int /*<<< orphan*/ ,struct ipu_ic_csc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_enable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (int /*<<< orphan*/ ,int) ; 
 int prp_setup_channel (struct prp_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prp_setup_vb2_buf (struct prp_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prp_unsetup_vb2_buf (struct prp_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int prp_setup_rotation(struct prp_priv *priv)
{
	struct imx_media_video_dev *vdev = priv->vdev;
	struct imx_ic_priv *ic_priv = priv->ic_priv;
	const struct imx_media_pixfmt *outcc, *incc;
	struct v4l2_mbus_framefmt *infmt;
	struct v4l2_pix_format *outfmt;
	struct ipu_ic_csc csc;
	dma_addr_t phys[2];
	int ret;

	infmt = &priv->format_mbus[PRPENCVF_SINK_PAD];
	outfmt = &vdev->fmt.fmt.pix;
	incc = priv->cc[PRPENCVF_SINK_PAD];
	outcc = vdev->cc;

	ret = ipu_ic_calc_csc(&csc,
			      infmt->ycbcr_enc, infmt->quantization,
			      incc->cs,
			      outfmt->ycbcr_enc, outfmt->quantization,
			      outcc->cs);
	if (ret) {
		v4l2_err(&ic_priv->sd, "ipu_ic_calc_csc failed, %d\n",
			 ret);
		return ret;
	}

	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0],
				      outfmt->sizeimage);
	if (ret) {
		v4l2_err(&ic_priv->sd, "failed to alloc rot_buf[0], %d\n", ret);
		return ret;
	}
	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1],
				      outfmt->sizeimage);
	if (ret) {
		v4l2_err(&ic_priv->sd, "failed to alloc rot_buf[1], %d\n", ret);
		goto free_rot0;
	}

	ret = ipu_ic_task_init(priv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->height, outfmt->width);
	if (ret) {
		v4l2_err(&ic_priv->sd, "ipu_ic_task_init failed, %d\n", ret);
		goto free_rot1;
	}

	/* init the IC-PRP-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->out_ch, IPU_ROTATE_NONE,
				priv->rot_buf[0].phys, priv->rot_buf[1].phys,
				true);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(out_ch) failed, %d\n", ret);
		goto free_rot1;
	}

	/* init the MEM-->IC-PRP ROT IDMAC channel */
	ret = prp_setup_channel(priv, priv->rot_in_ch, priv->rot_mode,
				priv->rot_buf[0].phys, priv->rot_buf[1].phys,
				true);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(rot_in_ch) failed, %d\n", ret);
		goto free_rot1;
	}

	prp_setup_vb2_buf(priv, phys);

	/* init the destination IC-PRP ROT-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->rot_out_ch, IPU_ROTATE_NONE,
				phys[0], phys[1],
				false);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(rot_out_ch) failed, %d\n", ret);
		goto unsetup_vb2;
	}

	/* now link IC-PRP-->MEM to MEM-->IC-PRP ROT */
	ipu_idmac_link(priv->out_ch, priv->rot_in_ch);

	/* enable the IC */
	ipu_ic_enable(priv->ic);

	/* set buffers ready */
	ipu_idmac_select_buffer(priv->out_ch, 0);
	ipu_idmac_select_buffer(priv->out_ch, 1);
	ipu_idmac_select_buffer(priv->rot_out_ch, 0);
	ipu_idmac_select_buffer(priv->rot_out_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->out_ch);
	ipu_idmac_enable_channel(priv->rot_in_ch);
	ipu_idmac_enable_channel(priv->rot_out_ch);

	/* and finally enable the IC PRP task */
	ipu_ic_task_enable(priv->ic);

	return 0;

unsetup_vb2:
	prp_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
free_rot1:
	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1]);
free_rot0:
	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0]);
	return ret;
}