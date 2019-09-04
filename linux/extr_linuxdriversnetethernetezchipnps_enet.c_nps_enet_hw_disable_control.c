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
struct nps_enet_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_ENET_REG_BUF_INT_ENABLE ; 
 int /*<<< orphan*/  NPS_ENET_REG_GE_MAC_CFG_0 ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_reg_set (struct nps_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nps_enet_hw_disable_control(struct net_device *ndev)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);

	/* Disable interrupts */
	nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);

	/* Disable Rx and Tx */
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_0, 0);
}