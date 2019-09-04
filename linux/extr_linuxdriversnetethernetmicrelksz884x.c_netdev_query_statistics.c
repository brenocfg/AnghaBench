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
struct net_device_stats {scalar_t__ tx_window_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ collisions; scalar_t__ multicast; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct ksz_port_mib {scalar_t__* counter; } ;
struct ksz_port {int first_port; int mib_port_cnt; int /*<<< orphan*/ * counter; } ;
struct ksz_hw {struct ksz_port_mib* port_mib; } ;
struct dev_priv {TYPE_1__* adapter; struct ksz_port port; } ;
struct TYPE_2__ {struct ksz_hw hw; } ;

/* Variables and functions */
 size_t MIB_COUNTER_RX_ALIGNMENT_ERR ; 
 size_t MIB_COUNTER_RX_CRC_ERR ; 
 size_t MIB_COUNTER_RX_FRAGMENT ; 
 size_t MIB_COUNTER_RX_JABBER ; 
 size_t MIB_COUNTER_RX_MULTICAST ; 
 size_t MIB_COUNTER_RX_OVERSIZE ; 
 size_t MIB_COUNTER_RX_SYMBOL_ERR ; 
 size_t MIB_COUNTER_RX_UNDERSIZE ; 
 size_t MIB_COUNTER_TX_LATE_COLLISION ; 
 size_t MIB_COUNTER_TX_TOTAL_COLLISION ; 
 size_t OID_COUNTER_RCV_ERROR ; 
 size_t OID_COUNTER_XMIT_ERROR ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *netdev_query_statistics(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_port *port = &priv->port;
	struct ksz_hw *hw = &priv->adapter->hw;
	struct ksz_port_mib *mib;
	int i;
	int p;

	dev->stats.rx_errors = port->counter[OID_COUNTER_RCV_ERROR];
	dev->stats.tx_errors = port->counter[OID_COUNTER_XMIT_ERROR];

	/* Reset to zero to add count later. */
	dev->stats.multicast = 0;
	dev->stats.collisions = 0;
	dev->stats.rx_length_errors = 0;
	dev->stats.rx_crc_errors = 0;
	dev->stats.rx_frame_errors = 0;
	dev->stats.tx_window_errors = 0;

	for (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) {
		mib = &hw->port_mib[p];

		dev->stats.multicast += (unsigned long)
			mib->counter[MIB_COUNTER_RX_MULTICAST];

		dev->stats.collisions += (unsigned long)
			mib->counter[MIB_COUNTER_TX_TOTAL_COLLISION];

		dev->stats.rx_length_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_UNDERSIZE] +
			mib->counter[MIB_COUNTER_RX_FRAGMENT] +
			mib->counter[MIB_COUNTER_RX_OVERSIZE] +
			mib->counter[MIB_COUNTER_RX_JABBER]);
		dev->stats.rx_crc_errors += (unsigned long)
			mib->counter[MIB_COUNTER_RX_CRC_ERR];
		dev->stats.rx_frame_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_ALIGNMENT_ERR] +
			mib->counter[MIB_COUNTER_RX_SYMBOL_ERR]);

		dev->stats.tx_window_errors += (unsigned long)
			mib->counter[MIB_COUNTER_TX_LATE_COLLISION];
	}

	return &dev->stats;
}