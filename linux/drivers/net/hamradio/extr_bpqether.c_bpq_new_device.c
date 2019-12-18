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
struct net_device {int dummy; } ;
struct bpqdev {int /*<<< orphan*/  bpq_list; int /*<<< orphan*/  acpt_addr; int /*<<< orphan*/  dest_addr; struct net_device* axdev; struct net_device* ethdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpq_devices ; 
 int /*<<< orphan*/  bpq_setup ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bpqdev* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int bpq_new_device(struct net_device *edev)
{
	int err;
	struct net_device *ndev;
	struct bpqdev *bpq;

	ndev = alloc_netdev(sizeof(struct bpqdev), "bpq%d", NET_NAME_UNKNOWN,
			    bpq_setup);
	if (!ndev)
		return -ENOMEM;

		
	bpq = netdev_priv(ndev);
	dev_hold(edev);
	bpq->ethdev = edev;
	bpq->axdev = ndev;

	eth_broadcast_addr(bpq->dest_addr);
	eth_broadcast_addr(bpq->acpt_addr);

	err = register_netdevice(ndev);
	if (err)
		goto error;

	/* List protected by RTNL */
	list_add_rcu(&bpq->bpq_list, &bpq_devices);
	return 0;

 error:
	dev_put(edev);
	free_netdev(ndev);
	return err;
	
}