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
struct v4l2_pix_format {int /*<<< orphan*/  sizeimage; } ;
struct prp_priv {int last_eof; int nfb4eof; int /*<<< orphan*/  underrun_buf; void* nfb4eof_irq; void* eof_irq; int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  src_sd; int /*<<< orphan*/  out_ch; int /*<<< orphan*/  rot_out_ch; int /*<<< orphan*/  rot_mode; scalar_t__ frame_sequence; int /*<<< orphan*/  last_eof_comp; scalar_t__ ipu_buf_num; struct imx_media_video_dev* vdev; struct imx_ic_priv* ic_priv; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {TYPE_2__ fmt; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu_dev; int /*<<< orphan*/  sd; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  IPU_IRQ_EOF ; 
 int /*<<< orphan*/  IPU_IRQ_NFB4EOF ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,void*,struct prp_priv*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct prp_priv*) ; 
 int imx_media_alloc_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* ipu_idmac_channel_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipu_rot_mode_is_irt (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prp_eof_interrupt ; 
 int prp_get_ipu_resources (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_nfb4eof_interrupt ; 
 int /*<<< orphan*/  prp_put_ipu_resources (struct prp_priv*) ; 
 int prp_setup_norotation (struct prp_priv*) ; 
 int prp_setup_rotation (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_unsetup (struct prp_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int prp_start(struct prp_priv *priv)
{
	struct imx_ic_priv *ic_priv = priv->ic_priv;
	struct imx_media_video_dev *vdev = priv->vdev;
	struct v4l2_pix_format *outfmt;
	int ret;

	ret = prp_get_ipu_resources(priv);
	if (ret)
		return ret;

	outfmt = &vdev->fmt.fmt.pix;

	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf,
				      outfmt->sizeimage);
	if (ret)
		goto out_put_ipu;

	priv->ipu_buf_num = 0;

	/* init EOF completion waitq */
	init_completion(&priv->last_eof_comp);
	priv->frame_sequence = 0;
	priv->last_eof = false;
	priv->nfb4eof = false;

	if (ipu_rot_mode_is_irt(priv->rot_mode))
		ret = prp_setup_rotation(priv);
	else
		ret = prp_setup_norotation(priv);
	if (ret)
		goto out_free_underrun;

	priv->nfb4eof_irq = ipu_idmac_channel_irq(ic_priv->ipu,
						  priv->out_ch,
						  IPU_IRQ_NFB4EOF);
	ret = devm_request_irq(ic_priv->ipu_dev, priv->nfb4eof_irq,
			       prp_nfb4eof_interrupt, 0,
			       "imx-ic-prp-nfb4eof", priv);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "Error registering NFB4EOF irq: %d\n", ret);
		goto out_unsetup;
	}

	if (ipu_rot_mode_is_irt(priv->rot_mode))
		priv->eof_irq = ipu_idmac_channel_irq(
			ic_priv->ipu, priv->rot_out_ch, IPU_IRQ_EOF);
	else
		priv->eof_irq = ipu_idmac_channel_irq(
			ic_priv->ipu, priv->out_ch, IPU_IRQ_EOF);

	ret = devm_request_irq(ic_priv->ipu_dev, priv->eof_irq,
			       prp_eof_interrupt, 0,
			       "imx-ic-prp-eof", priv);
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "Error registering eof irq: %d\n", ret);
		goto out_free_nfb4eof_irq;
	}

	/* start upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 1);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	if (ret) {
		v4l2_err(&ic_priv->sd,
			 "upstream stream on failed: %d\n", ret);
		goto out_free_eof_irq;
	}

	/* start the EOF timeout timer */
	mod_timer(&priv->eof_timeout_timer,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

	return 0;

out_free_eof_irq:
	devm_free_irq(ic_priv->ipu_dev, priv->eof_irq, priv);
out_free_nfb4eof_irq:
	devm_free_irq(ic_priv->ipu_dev, priv->nfb4eof_irq, priv);
out_unsetup:
	prp_unsetup(priv, VB2_BUF_STATE_QUEUED);
out_free_underrun:
	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf);
out_put_ipu:
	prp_put_ipu_resources(priv);
	return ret;
}