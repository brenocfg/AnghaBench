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
struct cw1200_common {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cw1200_upload_qosnull(struct cw1200_common *priv)
{
	/* TODO:  This needs to be implemented

	struct wsm_template_frame frame = {
		.frame_type = WSM_FRAME_TYPE_QOS_NULL,
		.rate = 0xFF,
	};

	frame.skb = ieee80211_qosnullfunc_get(priv->hw, priv->vif);
	if (!frame.skb)
		return -ENOMEM;

	ret = wsm_set_template_frame(priv, &frame);

	dev_kfree_skb(frame.skb);

	*/
	return 0;
}