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
typedef  int /*<<< orphan*/  u64 ;
struct slic_stats {int dummy; } ;
struct slic_device {struct slic_stats stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_GET_STATS_COUNTER (int /*<<< orphan*/ ,struct slic_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_errs ; 
 struct slic_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rx_buff_miss ; 
 int /*<<< orphan*/  rx_buffoflow ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_crc ; 
 int /*<<< orphan*/  rx_drbl ; 
 int /*<<< orphan*/  rx_early ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  rx_ipcsum ; 
 int /*<<< orphan*/  rx_iphlen ; 
 int /*<<< orphan*/  rx_iplen ; 
 int /*<<< orphan*/  rx_lcode ; 
 int /*<<< orphan*/  rx_mcasts ; 
 int /*<<< orphan*/  rx_oflow802 ; 
 int /*<<< orphan*/  rx_packets ; 
 int /*<<< orphan*/  rx_tpcsum ; 
 int /*<<< orphan*/  rx_tphlen ; 
 int /*<<< orphan*/  rx_tpoflow ; 
 int /*<<< orphan*/  rx_uflow802 ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_carrier ; 
 int /*<<< orphan*/  tx_dropped ; 
 int /*<<< orphan*/  tx_packets ; 

__attribute__((used)) static void slic_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *eth_stats, u64 *data)
{
	struct slic_device *sdev = netdev_priv(dev);
	struct slic_stats *stats = &sdev->stats;

	SLIC_GET_STATS_COUNTER(data[0], stats, rx_packets);
	SLIC_GET_STATS_COUNTER(data[1], stats, rx_bytes);
	SLIC_GET_STATS_COUNTER(data[2], stats, rx_mcasts);
	SLIC_GET_STATS_COUNTER(data[3], stats, rx_errors);
	SLIC_GET_STATS_COUNTER(data[4], stats, rx_buff_miss);
	SLIC_GET_STATS_COUNTER(data[5], stats, rx_tpcsum);
	SLIC_GET_STATS_COUNTER(data[6], stats, rx_tpoflow);
	SLIC_GET_STATS_COUNTER(data[7], stats, rx_tphlen);
	SLIC_GET_STATS_COUNTER(data[8], stats, rx_ipcsum);
	SLIC_GET_STATS_COUNTER(data[9], stats, rx_iplen);
	SLIC_GET_STATS_COUNTER(data[10], stats, rx_iphlen);
	SLIC_GET_STATS_COUNTER(data[11], stats, rx_early);
	SLIC_GET_STATS_COUNTER(data[12], stats, rx_buffoflow);
	SLIC_GET_STATS_COUNTER(data[13], stats, rx_lcode);
	SLIC_GET_STATS_COUNTER(data[14], stats, rx_drbl);
	SLIC_GET_STATS_COUNTER(data[15], stats, rx_crc);
	SLIC_GET_STATS_COUNTER(data[16], stats, rx_oflow802);
	SLIC_GET_STATS_COUNTER(data[17], stats, rx_uflow802);
	SLIC_GET_STATS_COUNTER(data[18], stats, tx_packets);
	SLIC_GET_STATS_COUNTER(data[19], stats, tx_bytes);
	SLIC_GET_STATS_COUNTER(data[20], stats, tx_carrier);
	SLIC_GET_STATS_COUNTER(data[21], stats, tx_dropped);
	SLIC_GET_STATS_COUNTER(data[22], stats, irq_errs);
}