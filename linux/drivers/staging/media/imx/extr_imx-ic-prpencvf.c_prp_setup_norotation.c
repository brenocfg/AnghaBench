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
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; } ;
struct prp_priv {int /*<<< orphan*/  ic; int /*<<< orphan*/  out_ch; int /*<<< orphan*/  rot_mode; struct imx_media_pixfmt** cc; struct v4l2_mbus_framefmt* format_mbus; struct imx_ic_priv* ic_priv; struct imx_media_video_dev* vdev; } ;
struct ipu_ic_csc {int dummy; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {struct imx_media_pixfmt* cc; TYPE_2__ fmt; } ;
struct imx_media_pixfmt {int /*<<< orphan*/  cs; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu; int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PRPENCVF_SINK_PAD ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  ipu_cpmem_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dump (int /*<<< orphan*/ ) ; 
 int ipu_ic_calc_csc (struct ipu_ic_csc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_task_enable (int /*<<< orphan*/ ) ; 
 int ipu_ic_task_init (int /*<<< orphan*/ ,struct ipu_ic_csc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_enable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (int /*<<< orphan*/ ,int) ; 
 int prp_setup_channel (struct prp_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prp_setup_vb2_buf (struct prp_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prp_unsetup_vb2_buf (struct prp_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int prp_setup_norotation(struct prp_priv *priv)
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

	ret = ipu_ic_task_init(priv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->width, outfmt->height);
	if (ret) {
		v4l2_err(&ic_priv->sd, "ipu_ic_task_init failed, %d\n", ret);
		return ret;
	}

	prp_setup_vb2_buf(priv, phys);

	/* init the IC PRP-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->out_ch, priv->rot_mode,
				phys[0], phys[1], false);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(out_ch) failed, %d\n", ret);
		goto unsetup_vb2;
	}

	ipu_cpmem_dump(priv->out_ch);
	ipu_ic_dump(priv->ic);
	ipu_dump(ic_priv->ipu);

	ipu_ic_enable(priv->ic);

	/* set buffers ready */
	ipu_idmac_select_buffer(priv->out_ch, 0);
	ipu_idmac_select_buffer(priv->out_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->out_ch);

	/* enable the IC task */
	ipu_ic_task_enable(priv->ic);

	return 0;

unsetup_vb2:
	prp_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
	return ret;
}