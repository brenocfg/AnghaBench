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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  rx_bd_num; int /*<<< orphan*/  rx_bd_r_index; int /*<<< orphan*/  rx_bd_w_index; int /*<<< orphan*/  tx_bd_num; int /*<<< orphan*/  tx_bd_w_index; int /*<<< orphan*/  tx_bd_r_index; int /*<<< orphan*/  tx_eapol; int /*<<< orphan*/  tx_reclaim_req; int /*<<< orphan*/  tx_reclaim_done; int /*<<< orphan*/  tx_done_count; int /*<<< orphan*/  tx_full_count; } ;
struct qtnf_pcie_topaz_state {int /*<<< orphan*/  ep_next_rx_pkt; struct qtnf_pcie_bus_priv base; } ;
struct qtnf_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qtnf_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtnf_dbg_pkt_stats(struct seq_file *s, void *data)
{
	struct qtnf_bus *bus = dev_get_drvdata(s->private);
	struct qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	struct qtnf_pcie_bus_priv *priv = &ts->base;
	u32 tx_done_index = readl(ts->ep_next_rx_pkt);

	seq_printf(s, "tx_full_count(%u)\n", priv->tx_full_count);
	seq_printf(s, "tx_done_count(%u)\n", priv->tx_done_count);
	seq_printf(s, "tx_reclaim_done(%u)\n", priv->tx_reclaim_done);
	seq_printf(s, "tx_reclaim_req(%u)\n", priv->tx_reclaim_req);
	seq_printf(s, "tx_eapol(%u)\n", priv->tx_eapol);

	seq_printf(s, "tx_bd_r_index(%u)\n", priv->tx_bd_r_index);
	seq_printf(s, "tx_done_index(%u)\n", tx_done_index);
	seq_printf(s, "tx_bd_w_index(%u)\n", priv->tx_bd_w_index);

	seq_printf(s, "tx host queue len(%u)\n",
		   CIRC_CNT(priv->tx_bd_w_index, priv->tx_bd_r_index,
			    priv->tx_bd_num));
	seq_printf(s, "tx reclaim queue len(%u)\n",
		   CIRC_CNT(tx_done_index, priv->tx_bd_r_index,
			    priv->tx_bd_num));
	seq_printf(s, "tx card queue len(%u)\n",
		   CIRC_CNT(priv->tx_bd_w_index, tx_done_index,
			    priv->tx_bd_num));

	seq_printf(s, "rx_bd_r_index(%u)\n", priv->rx_bd_r_index);
	seq_printf(s, "rx_bd_w_index(%u)\n", priv->rx_bd_w_index);
	seq_printf(s, "rx alloc queue len(%u)\n",
		   CIRC_SPACE(priv->rx_bd_w_index, priv->rx_bd_r_index,
			      priv->rx_bd_num));

	return 0;
}