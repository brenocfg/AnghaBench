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
struct TYPE_3__ {scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ power; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ operation_mode; int /*<<< orphan*/  power_mgmt; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  POWER_MGMT_ACTIVE ; 
 int /*<<< orphan*/  POWER_MGMT_SAVE1 ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_POW_MNGMT_REQUEST ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_power(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *vwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (vwrq->power.disabled) {
		priv->reg.power_mgmt = POWER_MGMT_ACTIVE;
	} else {
		if (priv->reg.operation_mode != MODE_INFRASTRUCTURE)
			return -EINVAL;
		priv->reg.power_mgmt = POWER_MGMT_SAVE1;
	}

	hostif_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);

	return 0;
}