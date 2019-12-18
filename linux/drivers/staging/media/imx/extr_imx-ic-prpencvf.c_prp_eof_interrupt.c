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
struct prp_priv {int last_eof; int ipu_buf_num; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  eof_timeout_timer; struct ipuv3_channel* out_ch; struct ipuv3_channel* rot_out_ch; int /*<<< orphan*/  rot_mode; int /*<<< orphan*/  last_eof_comp; } ;
struct ipuv3_channel {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (struct ipuv3_channel*,int) ; 
 scalar_t__ ipu_rot_mode_is_irt (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prp_vb2_buf_done (struct prp_priv*,struct ipuv3_channel*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t prp_eof_interrupt(int irq, void *dev_id)
{
	struct prp_priv *priv = dev_id;
	struct ipuv3_channel *channel;

	spin_lock(&priv->irqlock);

	if (priv->last_eof) {
		complete(&priv->last_eof_comp);
		priv->last_eof = false;
		goto unlock;
	}

	channel = (ipu_rot_mode_is_irt(priv->rot_mode)) ?
		priv->rot_out_ch : priv->out_ch;

	prp_vb2_buf_done(priv, channel);

	/* select new IPU buf */
	ipu_idmac_select_buffer(channel, priv->ipu_buf_num);
	/* toggle IPU double-buffer index */
	priv->ipu_buf_num ^= 1;

	/* bump the EOF timeout timer */
	mod_timer(&priv->eof_timeout_timer,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

unlock:
	spin_unlock(&priv->irqlock);
	return IRQ_HANDLED;
}