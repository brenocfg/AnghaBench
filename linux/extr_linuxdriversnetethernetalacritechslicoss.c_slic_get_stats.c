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
struct slic_stats {int dummy; } ;
struct slic_device {struct slic_stats stats; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_GET_STATS_COUNTER (int /*<<< orphan*/ ,struct slic_stats*,int /*<<< orphan*/ ) ; 
 struct slic_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rx_buff_miss ; 
 int /*<<< orphan*/  rx_buffoflow ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_crc ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  rx_mcasts ; 
 int /*<<< orphan*/  rx_oflow802 ; 
 int /*<<< orphan*/  rx_packets ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_carrier ; 
 int /*<<< orphan*/  tx_dropped ; 
 int /*<<< orphan*/  tx_packets ; 

__attribute__((used)) static void slic_get_stats(struct net_device *dev,
			   struct rtnl_link_stats64 *lst)
{
	struct slic_device *sdev = netdev_priv(dev);
	struct slic_stats *stats = &sdev->stats;

	SLIC_GET_STATS_COUNTER(lst->rx_packets, stats, rx_packets);
	SLIC_GET_STATS_COUNTER(lst->tx_packets, stats, tx_packets);
	SLIC_GET_STATS_COUNTER(lst->rx_bytes, stats, rx_bytes);
	SLIC_GET_STATS_COUNTER(lst->tx_bytes, stats, tx_bytes);
	SLIC_GET_STATS_COUNTER(lst->rx_errors, stats, rx_errors);
	SLIC_GET_STATS_COUNTER(lst->rx_dropped, stats, rx_buff_miss);
	SLIC_GET_STATS_COUNTER(lst->tx_dropped, stats, tx_dropped);
	SLIC_GET_STATS_COUNTER(lst->multicast, stats, rx_mcasts);
	SLIC_GET_STATS_COUNTER(lst->rx_over_errors, stats, rx_buffoflow);
	SLIC_GET_STATS_COUNTER(lst->rx_crc_errors, stats, rx_crc);
	SLIC_GET_STATS_COUNTER(lst->rx_fifo_errors, stats, rx_oflow802);
	SLIC_GET_STATS_COUNTER(lst->tx_carrier_errors, stats, tx_carrier);
}