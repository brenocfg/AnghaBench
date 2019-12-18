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
typedef  scalar_t__ u64 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  cb; } ;
struct net_device {int dummy; } ;
struct mlxsw_tx_info {int is_emad; int /*<<< orphan*/  local_port; } ;
struct mlxsw_sp_port_pcpu_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct mlxsw_sp_port {TYPE_1__* pcpu_stats; int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct mlxsw_skb_cb {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 scalar_t__ MLXSW_TXHDR_LEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_core_skb_transmit (int /*<<< orphan*/ ,struct sk_buff*,struct mlxsw_tx_info const*) ; 
 scalar_t__ mlxsw_core_skb_transmit_busy (int /*<<< orphan*/ ,struct mlxsw_tx_info const*) ; 
 int /*<<< orphan*/  mlxsw_sp_txhdr_construct (struct sk_buff*,struct mlxsw_tx_info const*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t mlxsw_sp_port_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_port_pcpu_stats *pcpu_stats;
	const struct mlxsw_tx_info tx_info = {
		.local_port = mlxsw_sp_port->local_port,
		.is_emad = false,
	};
	u64 len;
	int err;

	memset(skb->cb, 0, sizeof(struct mlxsw_skb_cb));

	if (mlxsw_core_skb_transmit_busy(mlxsw_sp->core, &tx_info))
		return NETDEV_TX_BUSY;

	if (unlikely(skb_headroom(skb) < MLXSW_TXHDR_LEN)) {
		struct sk_buff *skb_orig = skb;

		skb = skb_realloc_headroom(skb, MLXSW_TXHDR_LEN);
		if (!skb) {
			this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
			dev_kfree_skb_any(skb_orig);
			return NETDEV_TX_OK;
		}
		dev_consume_skb_any(skb_orig);
	}

	if (eth_skb_pad(skb)) {
		this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
		return NETDEV_TX_OK;
	}

	mlxsw_sp_txhdr_construct(skb, &tx_info);
	/* TX header is consumed by HW on the way so we shouldn't count its
	 * bytes as being sent.
	 */
	len = skb->len - MLXSW_TXHDR_LEN;

	/* Due to a race we might fail here because of a full queue. In that
	 * unlikely case we simply drop the packet.
	 */
	err = mlxsw_core_skb_transmit(mlxsw_sp->core, skb, &tx_info);

	if (!err) {
		pcpu_stats = this_cpu_ptr(mlxsw_sp_port->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	} else {
		this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
		dev_kfree_skb_any(skb);
	}
	return NETDEV_TX_OK;
}