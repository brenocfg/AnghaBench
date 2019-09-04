#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucc_geth_private {TYPE_4__* ug_regs; TYPE_3__* uccf; struct ucc_geth_info* ug_info; TYPE_1__* phydev; } ;
struct ucc_geth_info {int /*<<< orphan*/  extensionField; int /*<<< orphan*/  pausePeriod; int /*<<< orphan*/  transmitFlowControl; int /*<<< orphan*/  receiveFlowControl; int /*<<< orphan*/  aufc; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;
struct TYPE_8__ {int /*<<< orphan*/  maccfg1; int /*<<< orphan*/  uempr; } ;
struct TYPE_7__ {TYPE_2__* uf_regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  upsmr; } ;
struct TYPE_5__ {scalar_t__ autoneg; } ;

/* Variables and functions */
 int init_flow_control_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
uec_set_pauseparam(struct net_device *netdev,
                     struct ethtool_pauseparam *pause)
{
	struct ucc_geth_private *ugeth = netdev_priv(netdev);
	int ret = 0;

	ugeth->ug_info->receiveFlowControl = pause->rx_pause;
	ugeth->ug_info->transmitFlowControl = pause->tx_pause;

	if (ugeth->phydev->autoneg) {
		if (netif_running(netdev)) {
			/* FIXME: automatically restart */
			netdev_info(netdev, "Please re-open the interface\n");
		}
	} else {
		struct ucc_geth_info *ug_info = ugeth->ug_info;

		ret = init_flow_control_params(ug_info->aufc,
					ug_info->receiveFlowControl,
					ug_info->transmitFlowControl,
					ug_info->pausePeriod,
					ug_info->extensionField,
					&ugeth->uccf->uf_regs->upsmr,
					&ugeth->ug_regs->uempr,
					&ugeth->ug_regs->maccfg1);
	}

	return ret;
}