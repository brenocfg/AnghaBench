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
typedef  scalar_t__ u32 ;
struct pch_can_priv {TYPE_3__* regs; TYPE_1__* ndev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ifregs; } ;
struct TYPE_5__ {int /*<<< orphan*/  mcont; int /*<<< orphan*/  creq; int /*<<< orphan*/  cmask; } ;
struct TYPE_4__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int PCH_CMASK_CLRINTPND ; 
 int PCH_CMASK_RX_TX_GET ; 
 int PCH_IF_MCONT_DLC ; 
 scalar_t__ PCH_RX_OBJ_END ; 
 scalar_t__ PCH_TX_OBJ_END ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,scalar_t__) ; 
 scalar_t__ get_can_dlc (int) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pch_can_rw_msg_obj (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void pch_can_tx_complete(struct net_device *ndev, u32 int_stat)
{
	struct pch_can_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &(priv->ndev->stats);
	u32 dlc;

	can_get_echo_skb(ndev, int_stat - PCH_RX_OBJ_END - 1);
	iowrite32(PCH_CMASK_RX_TX_GET | PCH_CMASK_CLRINTPND,
		  &priv->regs->ifregs[1].cmask);
	pch_can_rw_msg_obj(&priv->regs->ifregs[1].creq, int_stat);
	dlc = get_can_dlc(ioread32(&priv->regs->ifregs[1].mcont) &
			  PCH_IF_MCONT_DLC);
	stats->tx_bytes += dlc;
	stats->tx_packets++;
	if (int_stat == PCH_TX_OBJ_END)
		netif_wake_queue(ndev);
}