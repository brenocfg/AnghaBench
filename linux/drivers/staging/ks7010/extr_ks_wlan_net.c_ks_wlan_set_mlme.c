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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; } ;
struct iw_request_info {int dummy; } ;
struct iw_mlme {scalar_t__ cmd; scalar_t__ reason_code; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IW_MLME_DEAUTH ; 
 scalar_t__ IW_MLME_DISASSOC ; 
 scalar_t__ SLP_SLEEP ; 
 scalar_t__ WLAN_REASON_MIC_FAILURE ; 
 int ks_wlan_set_stop_request (struct net_device*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_mlme(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_mlme *mlme = (struct iw_mlme *)extra;
	__u32 mode = 1;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (mlme->cmd != IW_MLME_DEAUTH &&
	    mlme->cmd != IW_MLME_DISASSOC)
		return -EOPNOTSUPP;

	if (mlme->cmd == IW_MLME_DEAUTH &&
	    mlme->reason_code == WLAN_REASON_MIC_FAILURE)
		return 0;

	return ks_wlan_set_stop_request(dev, NULL, &mode, NULL);
}