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
struct pvc_device {int dummy; } ;
struct net_device {int min_mtu; int needs_free_netdev; struct pvc_device* ml_priv; int /*<<< orphan*/  priv_flags; void* max_mtu; void* mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  broadcast; scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int dce_changed; int /*<<< orphan*/  dce_pvc_count; } ;

/* Variables and functions */
 int ARPHRD_ETHER ; 
 int EEXIST ; 
 int EIO ; 
 int ENOBUFS ; 
 void* HDLC_MAX_MTU ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct pvc_device* add_pvc (struct net_device*,unsigned int) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_unused_pvcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  dlci_to_q922 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device** get_dev_p (struct pvc_device*,int) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int pvc_is_used (struct pvc_device*) ; 
 int /*<<< orphan*/  pvc_ops ; 
 int /*<<< orphan*/  pvc_setup ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 TYPE_1__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fr_add_pvc(struct net_device *frad, unsigned int dlci, int type)
{
	hdlc_device *hdlc = dev_to_hdlc(frad);
	struct pvc_device *pvc;
	struct net_device *dev;
	int used;

	if ((pvc = add_pvc(frad, dlci)) == NULL) {
		netdev_warn(frad, "Memory squeeze on fr_add_pvc()\n");
		return -ENOBUFS;
	}

	if (*get_dev_p(pvc, type))
		return -EEXIST;

	used = pvc_is_used(pvc);

	if (type == ARPHRD_ETHER)
		dev = alloc_netdev(0, "pvceth%d", NET_NAME_UNKNOWN,
				   ether_setup);
	else
		dev = alloc_netdev(0, "pvc%d", NET_NAME_UNKNOWN, pvc_setup);

	if (!dev) {
		netdev_warn(frad, "Memory squeeze on fr_pvc()\n");
		delete_unused_pvcs(hdlc);
		return -ENOBUFS;
	}

	if (type == ARPHRD_ETHER) {
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		eth_hw_addr_random(dev);
	} else {
		*(__be16*)dev->dev_addr = htons(dlci);
		dlci_to_q922(dev->broadcast, dlci);
	}
	dev->netdev_ops = &pvc_ops;
	dev->mtu = HDLC_MAX_MTU;
	dev->min_mtu = 68;
	dev->max_mtu = HDLC_MAX_MTU;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->ml_priv = pvc;

	if (register_netdevice(dev) != 0) {
		free_netdev(dev);
		delete_unused_pvcs(hdlc);
		return -EIO;
	}

	dev->needs_free_netdev = true;
	*get_dev_p(pvc, type) = dev;
	if (!used) {
		state(hdlc)->dce_changed = 1;
		state(hdlc)->dce_pvc_count++;
	}
	return 0;
}