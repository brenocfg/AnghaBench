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
struct dpni_taildrop {int enable; int /*<<< orphan*/  threshold; int /*<<< orphan*/  member_0; } ;
struct dpaa2_eth_priv {int rx_td_enabled; int num_fqs; int /*<<< orphan*/  net_dev; TYPE_1__* fq; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  flowid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_TAILDROP_THRESH ; 
 scalar_t__ DPAA2_RX_FQ ; 
 int /*<<< orphan*/  DPNI_CP_QUEUE ; 
 int /*<<< orphan*/  DPNI_QUEUE_RX ; 
 int dpni_set_taildrop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_taildrop*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dpaa2_eth_set_rx_taildrop(struct dpaa2_eth_priv *priv, bool enable)
{
	struct dpni_taildrop td = {0};
	int i, err;

	if (priv->rx_td_enabled == enable)
		return;

	td.enable = enable;
	td.threshold = DPAA2_ETH_TAILDROP_THRESH;

	for (i = 0; i < priv->num_fqs; i++) {
		if (priv->fq[i].type != DPAA2_RX_FQ)
			continue;
		err = dpni_set_taildrop(priv->mc_io, 0, priv->mc_token,
					DPNI_CP_QUEUE, DPNI_QUEUE_RX, 0,
					priv->fq[i].flowid, &td);
		if (err) {
			netdev_err(priv->net_dev,
				   "dpni_set_taildrop() failed\n");
			break;
		}
	}

	priv->rx_td_enabled = enable;
}