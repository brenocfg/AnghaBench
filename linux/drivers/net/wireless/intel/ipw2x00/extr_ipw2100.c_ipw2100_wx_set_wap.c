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
struct TYPE_2__ {scalar_t__ sa_family; int /*<<< orphan*/ * sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  mandatory_bssid_mac; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  CFG_STATIC_BSSID ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_mandatory_bssid (struct ipw2100_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_wap(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0;

	// sanity checks
	if (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		return -EINVAL;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (is_broadcast_ether_addr(wrqu->ap_addr.sa_data) ||
	    is_zero_ether_addr(wrqu->ap_addr.sa_data)) {
		/* we disable mandatory BSSID association */
		IPW_DEBUG_WX("exit - disable mandatory BSSID\n");
		priv->config &= ~CFG_STATIC_BSSID;
		err = ipw2100_set_mandatory_bssid(priv, NULL, 0);
		goto done;
	}

	priv->config |= CFG_STATIC_BSSID;
	memcpy(priv->mandatory_bssid_mac, wrqu->ap_addr.sa_data, ETH_ALEN);

	err = ipw2100_set_mandatory_bssid(priv, wrqu->ap_addr.sa_data, 0);

	IPW_DEBUG_WX("SET BSSID -> %pM\n", wrqu->ap_addr.sa_data);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}