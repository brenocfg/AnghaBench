#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct prp_priv {int last_eof; int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  underrun_buf; int /*<<< orphan*/  nfb4eof_irq; int /*<<< orphan*/  eof_irq; int /*<<< orphan*/  src_sd; int /*<<< orphan*/  last_eof_comp; int /*<<< orphan*/  irqlock; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu_dev; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct prp_priv*) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prp_put_ipu_resources (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_unsetup (struct prp_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  video ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_stop(struct prp_priv *priv)
{
	struct imx_ic_priv *ic_priv = priv->ic_priv;
	unsigned long flags;
	int ret;

	/* mark next EOF interrupt as the last before stream off */
	spin_lock_irqsave(&priv->irqlock, flags);
	priv->last_eof = true;
	spin_unlock_irqrestore(&priv->irqlock, flags);

	/*
	 * and then wait for interrupt handler to mark completion.
	 */
	ret = wait_for_completion_timeout(
		&priv->last_eof_comp,
		msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (ret == 0)
		v4l2_warn(&ic_priv->sd, "wait last EOF timeout\n");

	/* stop upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 0);
	if (ret && ret != -ENOIOCTLCMD)
		v4l2_warn(&ic_priv->sd,
			  "upstream stream off failed: %d\n", ret);

	devm_free_irq(ic_priv->ipu_dev, priv->eof_irq, priv);
	devm_free_irq(ic_priv->ipu_dev, priv->nfb4eof_irq, priv);

	prp_unsetup(priv, VB2_BUF_STATE_ERROR);

	imx_media_free_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf);

	/* cancel the EOF timeout timer */
	del_timer_sync(&priv->eof_timeout_timer);

	prp_put_ipu_resources(priv);
}