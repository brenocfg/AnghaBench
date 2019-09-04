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
struct xge_stats {scalar_t__ rx_errors; scalar_t__ rx_bytes; scalar_t__ rx_packets; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct xge_pdata {struct xge_stats stats; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xge_pdata* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xge_get_stats64(struct net_device *ndev,
			    struct rtnl_link_stats64 *storage)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct xge_stats *stats = &pdata->stats;

	storage->tx_packets += stats->tx_packets;
	storage->tx_bytes += stats->tx_bytes;

	storage->rx_packets += stats->rx_packets;
	storage->rx_bytes += stats->rx_bytes;
	storage->rx_errors += stats->rx_errors;
}