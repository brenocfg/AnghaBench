#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ iw_mode; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int islpci_reset (TYPE_1__*,int) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  prism54_bring_down (TYPE_1__*) ; 

__attribute__((used)) static int
islpci_open(struct net_device *ndev)
{
	u32 rc;
	islpci_private *priv = netdev_priv(ndev);

	/* reset data structures, upload firmware and reset device */
	rc = islpci_reset(priv,1);
	if (rc) {
		prism54_bring_down(priv);
		return rc; /* Returns informative message */
	}

	netif_start_queue(ndev);

	/* Turn off carrier if in STA or Ad-hoc mode. It will be turned on
	 * once the firmware receives a trap of being associated
	 * (GEN_OID_LINKSTATE). In other modes (AP or WDS or monitor) we
	 * should just leave the carrier on as its expected the firmware
	 * won't send us a trigger. */
	if (priv->iw_mode == IW_MODE_INFRA || priv->iw_mode == IW_MODE_ADHOC)
		netif_carrier_off(ndev);
	else
		netif_carrier_on(ndev);

	return 0;
}