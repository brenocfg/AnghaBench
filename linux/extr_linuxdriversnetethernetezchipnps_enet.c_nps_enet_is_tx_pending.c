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
struct nps_enet_priv {scalar_t__ tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_ENET_REG_TX_CTL ; 
 int TX_CTL_CT_MASK ; 
 int TX_CTL_CT_SHIFT ; 
 int nps_enet_reg_get (struct nps_enet_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nps_enet_is_tx_pending(struct nps_enet_priv *priv)
{
	u32 tx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_TX_CTL);
	u32 tx_ctrl_ct = (tx_ctrl_value & TX_CTL_CT_MASK) >> TX_CTL_CT_SHIFT;

	return (!tx_ctrl_ct && priv->tx_skb);
}