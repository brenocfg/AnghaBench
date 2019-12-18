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
struct queue_set {int /*<<< orphan*/  sq_len; int /*<<< orphan*/  cq_len; } ;
struct nicvf {struct queue_set* qs; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMP_QUEUE_LEN ; 
 int /*<<< orphan*/  MAX_SND_QUEUE_LEN ; 
 struct nicvf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nicvf_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct nicvf *nic = netdev_priv(netdev);
	struct queue_set *qs = nic->qs;

	ring->rx_max_pending = MAX_CMP_QUEUE_LEN;
	ring->rx_pending = qs->cq_len;
	ring->tx_max_pending = MAX_SND_QUEUE_LEN;
	ring->tx_pending = qs->sq_len;
}