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
struct TYPE_2__ {scalar_t__ operation_mode; scalar_t__ power_mgmt; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 scalar_t__ POWER_MGMT_ACTIVE ; 
 scalar_t__ POWER_MGMT_SAVE1 ; 
 scalar_t__ POWER_MGMT_SAVE2 ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_POW_MNGMT_REQUEST ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_power_mgmt(struct net_device *dev,
				  struct iw_request_info *info, __u32 *uwrq,
				  char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (*uwrq != POWER_MGMT_ACTIVE &&
	    *uwrq != POWER_MGMT_SAVE1 &&
	    *uwrq != POWER_MGMT_SAVE2)
		return -EINVAL;

	if ((*uwrq == POWER_MGMT_SAVE1 || *uwrq == POWER_MGMT_SAVE2) &&
	    (priv->reg.operation_mode != MODE_INFRASTRUCTURE))
		return -EINVAL;

	priv->reg.power_mgmt = *uwrq;
	hostif_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);

	return 0;
}