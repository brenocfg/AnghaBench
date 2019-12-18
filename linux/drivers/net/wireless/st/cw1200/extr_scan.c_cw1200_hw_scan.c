#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wsm_template_frame {scalar_t__ skb; int /*<<< orphan*/  frame_type; } ;
struct wsm_ssid {scalar_t__ length; int /*<<< orphan*/ * ssid; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_scan_request {int n_ssids; size_t n_channels; TYPE_2__* ssids; int /*<<< orphan*/ * channels; scalar_t__ ie_len; int /*<<< orphan*/  ie; } ;
struct ieee80211_scan_request {struct cfg80211_scan_request req; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct cw1200_common* priv; } ;
struct TYPE_6__ {size_t n_ssids; int /*<<< orphan*/  work; struct wsm_ssid* ssids; int /*<<< orphan*/  output_power; int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; int /*<<< orphan*/ * curr; scalar_t__ status; struct cfg80211_scan_request* req; int /*<<< orphan*/  lock; } ;
struct cw1200_common {scalar_t__ join_status; TYPE_3__ scan; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  output_power; TYPE_1__* vif; } ;
struct TYPE_5__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct cfg80211_scan_request*) ; 
 scalar_t__ CW1200_JOIN_STATUS_AP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WSM_FRAME_TYPE_PROBE_REQUEST ; 
 int WSM_SCAN_MAX_NUM_OF_SSIDS ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_probereq_get (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wsm_lock_tx (struct cw1200_common*) ; 
 int wsm_set_probe_responder (struct cw1200_common*,int) ; 
 int wsm_set_template_frame (struct cw1200_common*,struct wsm_template_frame*) ; 

int cw1200_hw_scan(struct ieee80211_hw *hw,
		   struct ieee80211_vif *vif,
		   struct ieee80211_scan_request *hw_req)
{
	struct cw1200_common *priv = hw->priv;
	struct cfg80211_scan_request *req = &hw_req->req;
	struct wsm_template_frame frame = {
		.frame_type = WSM_FRAME_TYPE_PROBE_REQUEST,
	};
	int i, ret;

	if (!priv->vif)
		return -EINVAL;

	/* Scan when P2P_GO corrupt firmware MiniAP mode */
	if (priv->join_status == CW1200_JOIN_STATUS_AP)
		return -EOPNOTSUPP;

	if (req->n_ssids == 1 && !req->ssids[0].ssid_len)
		req->n_ssids = 0;

	wiphy_dbg(hw->wiphy, "[SCAN] Scan request for %d SSIDs.\n",
		  req->n_ssids);

	if (req->n_ssids > WSM_SCAN_MAX_NUM_OF_SSIDS)
		return -EINVAL;

	/* will be unlocked in cw1200_scan_work() */
	down(&priv->scan.lock);
	mutex_lock(&priv->conf_mutex);

	frame.skb = ieee80211_probereq_get(hw, priv->vif->addr, NULL, 0,
		req->ie_len);
	if (!frame.skb) {
		mutex_unlock(&priv->conf_mutex);
		up(&priv->scan.lock);
		return -ENOMEM;
	}

	if (req->ie_len)
		skb_put_data(frame.skb, req->ie, req->ie_len);

	ret = wsm_set_template_frame(priv, &frame);
	if (!ret) {
		/* Host want to be the probe responder. */
		ret = wsm_set_probe_responder(priv, true);
	}
	if (ret) {
		dev_kfree_skb(frame.skb);
		mutex_unlock(&priv->conf_mutex);
		up(&priv->scan.lock);
		return ret;
	}

	wsm_lock_tx(priv);

	BUG_ON(priv->scan.req);
	priv->scan.req = req;
	priv->scan.n_ssids = 0;
	priv->scan.status = 0;
	priv->scan.begin = &req->channels[0];
	priv->scan.curr = priv->scan.begin;
	priv->scan.end = &req->channels[req->n_channels];
	priv->scan.output_power = priv->output_power;

	for (i = 0; i < req->n_ssids; ++i) {
		struct wsm_ssid *dst = &priv->scan.ssids[priv->scan.n_ssids];
		memcpy(&dst->ssid[0], req->ssids[i].ssid, sizeof(dst->ssid));
		dst->length = req->ssids[i].ssid_len;
		++priv->scan.n_ssids;
	}

	if (frame.skb)
		dev_kfree_skb(frame.skb);
	mutex_unlock(&priv->conf_mutex);
	queue_work(priv->workqueue, &priv->scan.work);
	return 0;
}