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
typedef  size_t u32 ;
struct stmmac_priv {TYPE_2__* plat; int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {size_t tx_queues_to_use; TYPE_1__* tx_queues_cfg; } ;
struct TYPE_3__ {size_t mode_to_use; int /*<<< orphan*/  low_credit; int /*<<< orphan*/  high_credit; int /*<<< orphan*/  idle_slope; int /*<<< orphan*/  send_slope; } ;

/* Variables and functions */
 size_t MTL_QUEUE_DCB ; 
 int /*<<< orphan*/  stmmac_config_cbs (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void stmmac_configure_cbs(struct stmmac_priv *priv)
{
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 mode_to_use;
	u32 queue;

	/* queue 0 is reserved for legacy traffic */
	for (queue = 1; queue < tx_queues_count; queue++) {
		mode_to_use = priv->plat->tx_queues_cfg[queue].mode_to_use;
		if (mode_to_use == MTL_QUEUE_DCB)
			continue;

		stmmac_config_cbs(priv, priv->hw,
				priv->plat->tx_queues_cfg[queue].send_slope,
				priv->plat->tx_queues_cfg[queue].idle_slope,
				priv->plat->tx_queues_cfg[queue].high_credit,
				priv->plat->tx_queues_cfg[queue].low_credit,
				queue);
	}
}