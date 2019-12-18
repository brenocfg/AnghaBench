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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wmi_cancel_remain_on_chnl_event {int /*<<< orphan*/  status; int /*<<< orphan*/  duration; int /*<<< orphan*/  freq; } ;
struct wmi {struct ath6kl* parent_dev; } ;
struct ieee80211_channel {int dummy; } ;
struct ath6kl_vif {scalar_t__ last_cancel_roc_id; scalar_t__ last_roc_id; int /*<<< orphan*/  wdev; } ;
struct ath6kl {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (int /*<<< orphan*/ *,scalar_t__,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_cancel_remain_on_chnl_event_rx(struct wmi *wmi,
						     u8 *datap, int len,
						     struct ath6kl_vif *vif)
{
	struct wmi_cancel_remain_on_chnl_event *ev;
	u32 freq;
	u32 dur;
	struct ieee80211_channel *chan;
	struct ath6kl *ar = wmi->parent_dev;
	u32 id;

	if (len < sizeof(*ev))
		return -EINVAL;

	ev = (struct wmi_cancel_remain_on_chnl_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dur = le32_to_cpu(ev->duration);
	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "cancel_remain_on_chnl: freq=%u dur=%u status=%u\n",
		   freq, dur, ev->status);
	chan = ieee80211_get_channel(ar->wiphy, freq);
	if (!chan) {
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "cancel_remain_on_chnl: Unknown channel (freq=%u)\n",
			   freq);
		return -EINVAL;
	}
	if (vif->last_cancel_roc_id &&
	    vif->last_cancel_roc_id + 1 == vif->last_roc_id)
		id = vif->last_cancel_roc_id; /* event for cancel command */
	else
		id = vif->last_roc_id; /* timeout on uncanceled r-o-c */
	vif->last_cancel_roc_id = 0;
	cfg80211_remain_on_channel_expired(&vif->wdev, id, chan, GFP_ATOMIC);

	return 0;
}