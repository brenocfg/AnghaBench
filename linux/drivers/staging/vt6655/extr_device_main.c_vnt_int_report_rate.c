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
typedef  int u8 ;
typedef  int u16 ;
struct vnt_tx_fifo_head {int /*<<< orphan*/  fifo_ctl; } ;
struct vnt_td_info {int /*<<< orphan*/  skb; scalar_t__ buf; } ;
struct vnt_private {int /*<<< orphan*/  hw; } ;
struct TYPE_8__ {TYPE_3__* rates; } ;
struct TYPE_6__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {scalar_t__ band; int flags; TYPE_4__ status; TYPE_2__ control; } ;
struct ieee80211_rate {int hw_value; } ;
typedef  int s8 ;
struct TYPE_7__ {int count; int idx; } ;
struct TYPE_5__ {int idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FIFOCTL_AUTO_FB_0 ; 
 int FIFOCTL_AUTO_FB_1 ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_NOACK_TRANSMITTED ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int RATE_18M ; 
 int RATE_6M ; 
 int TSR0_NCR ; 
 int TSR1_TERR ; 
 int** fallback_rate0 ; 
 int** fallback_rate1 ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnt_int_report_rate(struct vnt_private *priv,
			       struct vnt_td_info *context, u8 tsr0, u8 tsr1)
{
	struct vnt_tx_fifo_head *fifo_head;
	struct ieee80211_tx_info *info;
	struct ieee80211_rate *rate;
	u16 fb_option;
	u8 tx_retry = (tsr0 & TSR0_NCR);
	s8 idx;

	if (!context)
		return -ENOMEM;

	if (!context->skb)
		return -EINVAL;

	fifo_head = (struct vnt_tx_fifo_head *)context->buf;
	fb_option = (le16_to_cpu(fifo_head->fifo_ctl) &
			(FIFOCTL_AUTO_FB_0 | FIFOCTL_AUTO_FB_1));

	info = IEEE80211_SKB_CB(context->skb);
	idx = info->control.rates[0].idx;

	if (fb_option && !(tsr1 & TSR1_TERR)) {
		u8 tx_rate;
		u8 retry = tx_retry;

		rate = ieee80211_get_tx_rate(priv->hw, info);
		tx_rate = rate->hw_value - RATE_18M;

		if (retry > 4)
			retry = 4;

		if (fb_option & FIFOCTL_AUTO_FB_0)
			tx_rate = fallback_rate0[tx_rate][retry];
		else if (fb_option & FIFOCTL_AUTO_FB_1)
			tx_rate = fallback_rate1[tx_rate][retry];

		if (info->band == NL80211_BAND_5GHZ)
			idx = tx_rate - RATE_6M;
		else
			idx = tx_rate;
	}

	ieee80211_tx_info_clear_status(info);

	info->status.rates[0].count = tx_retry;

	if (!(tsr1 & TSR1_TERR)) {
		info->status.rates[0].idx = idx;

		if (info->flags & IEEE80211_TX_CTL_NO_ACK)
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		else
			info->flags |= IEEE80211_TX_STAT_ACK;
	}

	return 0;
}