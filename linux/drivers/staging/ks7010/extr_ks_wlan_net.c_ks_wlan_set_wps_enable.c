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
struct net_device {int dummy; } ;
struct TYPE_2__ {int wps_enabled; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ wps; } ;
struct iw_request_info {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_WPS_ENABLE_REQUEST ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_wps_enable(struct net_device *dev,
				  struct iw_request_info *info, __u32 *uwrq,
				  char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;
	/* for SLEEP MODE */
	if (*uwrq != 0 && *uwrq != 1)
		return -EINVAL;

	priv->wps.wps_enabled = *uwrq;
	hostif_sme_enqueue(priv, SME_WPS_ENABLE_REQUEST);

	return 0;
}