#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sme_flag; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ sme_i; scalar_t__ scan_ssid_len; int /*<<< orphan*/  scan_ssid; } ;
struct iw_scan_req {int /*<<< orphan*/  essid; scalar_t__ essid_len; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int IW_SCAN_THIS_ESSID ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_AP_SCAN ; 
 int /*<<< orphan*/  SME_BSS_SCAN_REQUEST ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_scan(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_scan_req *req = NULL;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	/* specified SSID SCAN */
	if (wrqu->data.length == sizeof(struct iw_scan_req) &&
	    wrqu->data.flags & IW_SCAN_THIS_ESSID) {
		req = (struct iw_scan_req *)extra;
		priv->scan_ssid_len = req->essid_len;
		memcpy(priv->scan_ssid, req->essid, priv->scan_ssid_len);
	} else {
		priv->scan_ssid_len = 0;
	}

	priv->sme_i.sme_flag |= SME_AP_SCAN;
	hostif_sme_enqueue(priv, SME_BSS_SCAN_REQUEST);

	/* At this point, just return to the user. */

	return 0;
}