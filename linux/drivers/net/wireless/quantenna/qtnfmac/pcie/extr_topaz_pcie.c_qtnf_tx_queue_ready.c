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
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  tx_full_count; int /*<<< orphan*/  tx_bd_num; int /*<<< orphan*/  tx_bd_r_index; int /*<<< orphan*/  tx_bd_w_index; } ;
struct qtnf_pcie_topaz_state {struct qtnf_pcie_bus_priv base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_topaz_data_tx_reclaim (struct qtnf_pcie_topaz_state*) ; 

__attribute__((used)) static int qtnf_tx_queue_ready(struct qtnf_pcie_topaz_state *ts)
{
	struct qtnf_pcie_bus_priv *priv = &ts->base;

	if (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
			priv->tx_bd_num)) {
		qtnf_topaz_data_tx_reclaim(ts);

		if (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
				priv->tx_bd_num)) {
			priv->tx_full_count++;
			return 0;
		}
	}

	return 1;
}