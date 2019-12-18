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
struct vnt_usb_send_context {scalar_t__ fb_option; int in_use; int /*<<< orphan*/  skb; } ;
struct vnt_private {int num_tx_context; int /*<<< orphan*/  hw; struct vnt_usb_send_context** tx_context; } ;
struct TYPE_8__ {TYPE_3__* rates; } ;
struct TYPE_6__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {scalar_t__ band; int /*<<< orphan*/  flags; TYPE_4__ status; TYPE_2__ control; } ;
struct ieee80211_rate {int hw_value; } ;
typedef  int s8 ;
struct TYPE_7__ {int count; int idx; } ;
struct TYPE_5__ {int idx; } ;

/* Variables and functions */
 scalar_t__ AUTO_FB_0 ; 
 scalar_t__ AUTO_FB_1 ; 
 int EINVAL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int RATE_18M ; 
 int RATE_6M ; 
 int TSR_RETRYTMO ; 
 int TSR_TMO ; 
 int** fallback_rate0 ; 
 int** fallback_rate1 ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnt_int_report_rate(struct vnt_private *priv, u8 pkt_no, u8 tsr)
{
	struct vnt_usb_send_context *context;
	struct ieee80211_tx_info *info;
	struct ieee80211_rate *rate;
	u8 tx_retry = (tsr & 0xf0) >> 4;
	s8 idx;

	if (pkt_no >= priv->num_tx_context)
		return -EINVAL;

	context = priv->tx_context[pkt_no];

	if (!context->skb)
		return -EINVAL;

	info = IEEE80211_SKB_CB(context->skb);
	idx = info->control.rates[0].idx;

	if (context->fb_option && !(tsr & (TSR_TMO | TSR_RETRYTMO))) {
		u8 tx_rate;
		u8 retry = tx_retry;

		rate = ieee80211_get_tx_rate(priv->hw, info);
		tx_rate = rate->hw_value - RATE_18M;

		if (retry > 4)
			retry = 4;

		if (context->fb_option == AUTO_FB_0)
			tx_rate = fallback_rate0[tx_rate][retry];
		else if (context->fb_option == AUTO_FB_1)
			tx_rate = fallback_rate1[tx_rate][retry];

		if (info->band == NL80211_BAND_5GHZ)
			idx = tx_rate - RATE_6M;
		else
			idx = tx_rate;
	}

	ieee80211_tx_info_clear_status(info);

	info->status.rates[0].count = tx_retry;

	if (!(tsr & (TSR_TMO | TSR_RETRYTMO))) {
		info->status.rates[0].idx = idx;
		info->flags |= IEEE80211_TX_STAT_ACK;
	}

	ieee80211_tx_status_irqsafe(priv->hw, context->skb);

	context->in_use = false;

	return 0;
}