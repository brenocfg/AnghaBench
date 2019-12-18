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
struct csi_priv {int last_eof; int ipu_buf_num; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  idmac_ch; scalar_t__ fim; int /*<<< orphan*/  last_eof_comp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csi_vb2_buf_done (struct csi_priv*) ; 
 int /*<<< orphan*/  imx_media_fim_eof_monitor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t csi_idmac_eof_interrupt(int irq, void *dev_id)
{
	struct csi_priv *priv = dev_id;

	spin_lock(&priv->irqlock);

	if (priv->last_eof) {
		complete(&priv->last_eof_comp);
		priv->last_eof = false;
		goto unlock;
	}

	if (priv->fim)
		/* call frame interval monitor */
		imx_media_fim_eof_monitor(priv->fim, ktime_get());

	csi_vb2_buf_done(priv);

	/* select new IPU buf */
	ipu_idmac_select_buffer(priv->idmac_ch, priv->ipu_buf_num);
	/* toggle IPU double-buffer index */
	priv->ipu_buf_num ^= 1;

	/* bump the EOF timeout timer */
	mod_timer(&priv->eof_timeout_timer,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

unlock:
	spin_unlock(&priv->irqlock);
	return IRQ_HANDLED;
}