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
struct net_device {int flags; int tx_queue_len; int /*<<< orphan*/ * ethtool_ops; scalar_t__ mtu; int /*<<< orphan*/  type; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct hso_net {int /*<<< orphan*/  net_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 scalar_t__ DEFAULT_MTU ; 
 int /*<<< orphan*/  HSO_NET_TX_TIMEOUT ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  hso_dbg (int,char*,int) ; 
 int /*<<< orphan*/  hso_netdev_ops ; 
 struct hso_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hso_net_init(struct net_device *net)
{
	struct hso_net *hso_net = netdev_priv(net);

	hso_dbg(0x1, "sizeof hso_net is %zu\n", sizeof(*hso_net));

	/* fill in the other fields */
	net->netdev_ops = &hso_netdev_ops;
	net->watchdog_timeo = HSO_NET_TX_TIMEOUT;
	net->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	net->type = ARPHRD_NONE;
	net->mtu = DEFAULT_MTU - 14;
	net->tx_queue_len = 10;
	net->ethtool_ops = &ops;

	/* and initialize the semaphore */
	spin_lock_init(&hso_net->net_lock);
}