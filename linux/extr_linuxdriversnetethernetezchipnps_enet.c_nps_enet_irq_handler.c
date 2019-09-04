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
typedef  int u32 ;
struct nps_enet_priv {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NPS_ENET_REG_BUF_INT_ENABLE ; 
 int /*<<< orphan*/  NPS_ENET_REG_RX_CTL ; 
 int RX_CTL_CR_MASK ; 
 int RX_CTL_CR_SHIFT ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ nps_enet_is_tx_pending (struct nps_enet_priv*) ; 
 int nps_enet_reg_get (struct nps_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nps_enet_reg_set (struct nps_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t nps_enet_irq_handler(s32 irq, void *dev_instance)
{
	struct net_device *ndev = dev_instance;
	struct nps_enet_priv *priv = netdev_priv(ndev);
	u32 rx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_RX_CTL);
	u32 rx_ctrl_cr = (rx_ctrl_value & RX_CTL_CR_MASK) >> RX_CTL_CR_SHIFT;

	if (nps_enet_is_tx_pending(priv) || rx_ctrl_cr)
		if (likely(napi_schedule_prep(&priv->napi))) {
			nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);
			__napi_schedule(&priv->napi);
		}

	return IRQ_HANDLED;
}