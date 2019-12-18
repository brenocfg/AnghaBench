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
struct wsm_template_frame {int rate; int /*<<< orphan*/  skb; int /*<<< orphan*/  frame_type; } ;
struct cw1200_common {int /*<<< orphan*/  vif; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_FRAME_TYPE_PS_POLL ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_pspoll_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wsm_set_template_frame (struct cw1200_common*,struct wsm_template_frame*) ; 

__attribute__((used)) static int cw1200_upload_pspoll(struct cw1200_common *priv)
{
	int ret = 0;
	struct wsm_template_frame frame = {
		.frame_type = WSM_FRAME_TYPE_PS_POLL,
		.rate = 0xFF,
	};


	frame.skb = ieee80211_pspoll_get(priv->hw, priv->vif);
	if (!frame.skb)
		return -ENOMEM;

	ret = wsm_set_template_frame(priv, &frame);

	dev_kfree_skb(frame.skb);

	return ret;
}