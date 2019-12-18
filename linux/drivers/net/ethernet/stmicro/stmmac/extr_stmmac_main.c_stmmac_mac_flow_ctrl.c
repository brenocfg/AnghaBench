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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {int /*<<< orphan*/  pause; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  hw; TYPE_1__* plat; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmmac_flow_ctrl (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_mac_flow_ctrl(struct stmmac_priv *priv, u32 duplex)
{
	u32 tx_cnt = priv->plat->tx_queues_to_use;

	stmmac_flow_ctrl(priv, priv->hw, duplex, priv->flow_ctrl,
			priv->pause, tx_cnt);
}