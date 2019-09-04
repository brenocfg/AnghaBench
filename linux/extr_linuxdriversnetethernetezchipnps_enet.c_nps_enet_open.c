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
struct nps_enet_priv {int ge_mac_cfg_3_value; int /*<<< orphan*/  napi; int /*<<< orphan*/  irq; scalar_t__ ge_mac_cfg_2_value; int /*<<< orphan*/ * tx_skb; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CFG_3_MAX_LEN_SHIFT ; 
 int CFG_3_RX_IFG_TH_SHIFT ; 
 int NPS_ENET_GE_MAC_CFG_3_MAX_LEN ; 
 int NPS_ENET_GE_MAC_CFG_3_RX_IFG_TH ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_hw_disable_control (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_hw_enable_control (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_hw_reset (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_irq_handler ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static s32 nps_enet_open(struct net_device *ndev)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);
	s32 err;

	/* Reset private variables */
	priv->tx_skb = NULL;
	priv->ge_mac_cfg_2_value = 0;
	priv->ge_mac_cfg_3_value = 0;

	/* ge_mac_cfg_3 default values */
	priv->ge_mac_cfg_3_value |=
		 NPS_ENET_GE_MAC_CFG_3_RX_IFG_TH << CFG_3_RX_IFG_TH_SHIFT;

	priv->ge_mac_cfg_3_value |=
		 NPS_ENET_GE_MAC_CFG_3_MAX_LEN << CFG_3_MAX_LEN_SHIFT;

	/* Disable HW device */
	nps_enet_hw_disable_control(ndev);

	/* irq Rx allocation */
	err = request_irq(priv->irq, nps_enet_irq_handler,
			  0, "enet-rx-tx", ndev);
	if (err)
		return err;

	napi_enable(&priv->napi);

	/* Enable HW device */
	nps_enet_hw_reset(ndev);
	nps_enet_hw_enable_control(ndev);

	netif_start_queue(ndev);

	return 0;
}