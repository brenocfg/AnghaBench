#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ channel; } ;
struct wil6210_priv {int dummy; } ;
struct cfg80211_mgmt_tx_params {size_t len; int /*<<< orphan*/  wait; TYPE_1__* chan; int /*<<< orphan*/  offchan; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {int hw_value; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  cfg80211_mgmt_tx_status (struct wireless_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/ ) ; 
 struct wil6210_vif* wdev_to_vif (struct wil6210_priv*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_mgmt_tx (struct wil6210_vif*,int /*<<< orphan*/  const*,size_t) ; 
 int wmi_mgmt_tx_ext (struct wil6210_vif*,int /*<<< orphan*/  const*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 

int wil_cfg80211_mgmt_tx(struct wiphy *wiphy, struct wireless_dev *wdev,
			 struct cfg80211_mgmt_tx_params *params,
			 u64 *cookie)
{
	const u8 *buf = params->buf;
	size_t len = params->len;
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);
	int rc;
	bool tx_status;

	wil_dbg_misc(wil, "mgmt_tx: channel %d offchan %d, wait %d\n",
		     params->chan ? params->chan->hw_value : -1,
		     params->offchan,
		     params->wait);

	/* Note, currently we support the "wait" parameter only on AP mode.
	 * In other modes, user-space must call remain_on_channel before
	 * mgmt_tx or listen on a channel other than active one.
	 */

	if (params->chan && params->chan->hw_value == 0) {
		wil_err(wil, "invalid channel\n");
		return -EINVAL;
	}

	if (wdev->iftype != NL80211_IFTYPE_AP) {
		wil_dbg_misc(wil,
			     "send WMI_SW_TX_REQ_CMDID on non-AP interfaces\n");
		rc = wmi_mgmt_tx(vif, buf, len);
		goto out;
	}

	if (!params->chan || params->chan->hw_value == vif->channel) {
		wil_dbg_misc(wil,
			     "send WMI_SW_TX_REQ_CMDID for on-channel\n");
		rc = wmi_mgmt_tx(vif, buf, len);
		goto out;
	}

	if (params->offchan == 0) {
		wil_err(wil,
			"invalid channel params: current %d requested %d, off-channel not allowed\n",
			vif->channel, params->chan->hw_value);
		return -EBUSY;
	}

	/* use the wmi_mgmt_tx_ext only on AP mode and off-channel */
	rc = wmi_mgmt_tx_ext(vif, buf, len, params->chan->hw_value,
			     params->wait);

out:
	/* when the sent packet was not acked by receiver(ACK=0), rc will
	 * be -EAGAIN. In this case this function needs to return success,
	 * the ACK=0 will be reflected in tx_status.
	 */
	tx_status = (rc == 0);
	rc = (rc == -EAGAIN) ? 0 : rc;
	cfg80211_mgmt_tx_status(wdev, cookie ? *cookie : 0, buf, len,
				tx_status, GFP_KERNEL);

	return rc;
}