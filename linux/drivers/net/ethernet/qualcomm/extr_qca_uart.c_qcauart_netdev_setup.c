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
struct net_device {int tx_queue_len; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  QCAFRM_MAX_MTU ; 
 int /*<<< orphan*/  QCAFRM_MIN_MTU ; 
 int /*<<< orphan*/  QCAUART_TX_TIMEOUT ; 
 int /*<<< orphan*/  qcauart_netdev_ops ; 

__attribute__((used)) static void qcauart_netdev_setup(struct net_device *dev)
{
	dev->netdev_ops = &qcauart_netdev_ops;
	dev->watchdog_timeo = QCAUART_TX_TIMEOUT;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->tx_queue_len = 100;

	/* MTU range: 46 - 1500 */
	dev->min_mtu = QCAFRM_MIN_MTU;
	dev->max_mtu = QCAFRM_MAX_MTU;
}