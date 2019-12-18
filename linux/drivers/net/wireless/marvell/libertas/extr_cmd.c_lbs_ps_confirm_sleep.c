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
struct lbs_private {size_t resp_idx; int /*<<< orphan*/  driver_lock; scalar_t__* resp_len; int /*<<< orphan*/  event_fifo; scalar_t__ cur_cmd; scalar_t__ dnld_sent; } ;

/* Variables and functions */
 scalar_t__ kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_host (char*) ; 
 int /*<<< orphan*/  lbs_send_confirmsleep (struct lbs_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void lbs_ps_confirm_sleep(struct lbs_private *priv)
{
	unsigned long flags =0;
	int allowed = 1;

	spin_lock_irqsave(&priv->driver_lock, flags);
	if (priv->dnld_sent) {
		allowed = 0;
		lbs_deb_host("dnld_sent was set\n");
	}

	/* In-progress command? */
	if (priv->cur_cmd) {
		allowed = 0;
		lbs_deb_host("cur_cmd was set\n");
	}

	/* Pending events or command responses? */
	if (kfifo_len(&priv->event_fifo) || priv->resp_len[priv->resp_idx]) {
		allowed = 0;
		lbs_deb_host("pending events or command responses\n");
	}
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	if (allowed) {
		lbs_deb_host("sending lbs_ps_confirm_sleep\n");
		lbs_send_confirmsleep(priv);
	} else {
		lbs_deb_host("sleep confirm has been delayed\n");
	}
}