#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct dst_entry {int dummy; } ;
struct rtable {int rt_flags; struct dst_entry dst; } ;
struct net_device {int flags; unsigned int mtu; int /*<<< orphan*/  name; } ;
struct neighbour {struct net_device* dev; } ;
struct flowi4 {int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {TYPE_4__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct cxgbi_sock {int port_id; unsigned int mtu; TYPE_5__ saddr; TYPE_3__ daddr; int /*<<< orphan*/  csk_family; struct dst_entry* dst; struct cxgbi_device* cdev; } ;
struct cxgbi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int CXGBI_DBG_SOCK ; 
 int ENETDOWN ; 
 int ENETUNREACH ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct cxgbi_sock* ERR_PTR (int) ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct cxgbi_device* cxgbi_device_find_by_mac (struct net_device*,int*) ; 
 struct cxgbi_device* cxgbi_device_find_by_netdev (struct net_device*,int*) ; 
 struct cxgbi_sock* cxgbi_sock_create (struct cxgbi_device*) ; 
 struct neighbour* dst_neigh_lookup (struct dst_entry*,int /*<<< orphan*/ *) ; 
 struct rtable* find_route_ipv4 (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  log_debug (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cxgbi_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static struct cxgbi_sock *
cxgbi_check_route(struct sockaddr *dst_addr, int ifindex)
{
	struct sockaddr_in *daddr = (struct sockaddr_in *)dst_addr;
	struct dst_entry *dst;
	struct net_device *ndev;
	struct cxgbi_device *cdev;
	struct rtable *rt = NULL;
	struct neighbour *n;
	struct flowi4 fl4;
	struct cxgbi_sock *csk = NULL;
	unsigned int mtu = 0;
	int port = 0xFFFF;
	int err = 0;

	rt = find_route_ipv4(&fl4, 0, daddr->sin_addr.s_addr, 0,
			     daddr->sin_port, 0, ifindex);
	if (!rt) {
		pr_info("no route to ipv4 0x%x, port %u.\n",
			be32_to_cpu(daddr->sin_addr.s_addr),
			be16_to_cpu(daddr->sin_port));
		err = -ENETUNREACH;
		goto err_out;
	}
	dst = &rt->dst;
	n = dst_neigh_lookup(dst, &daddr->sin_addr.s_addr);
	if (!n) {
		err = -ENODEV;
		goto rel_rt;
	}
	ndev = n->dev;

	if (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) {
		pr_info("multi-cast route %pI4, port %u, dev %s.\n",
			&daddr->sin_addr.s_addr, ntohs(daddr->sin_port),
			ndev->name);
		err = -ENETUNREACH;
		goto rel_neigh;
	}

	if (ndev->flags & IFF_LOOPBACK) {
		ndev = ip_dev_find(&init_net, daddr->sin_addr.s_addr);
		if (!ndev) {
			err = -ENETUNREACH;
			goto rel_neigh;
		}
		mtu = ndev->mtu;
		pr_info("rt dev %s, loopback -> %s, mtu %u.\n",
			n->dev->name, ndev->name, mtu);
	}

	if (!(ndev->flags & IFF_UP) || !netif_carrier_ok(ndev)) {
		pr_info("%s interface not up.\n", ndev->name);
		err = -ENETDOWN;
		goto rel_neigh;
	}

	cdev = cxgbi_device_find_by_netdev(ndev, &port);
	if (!cdev)
		cdev = cxgbi_device_find_by_mac(ndev, &port);
	if (!cdev) {
		pr_info("dst %pI4, %s, NOT cxgbi device.\n",
			&daddr->sin_addr.s_addr, ndev->name);
		err = -ENETUNREACH;
		goto rel_neigh;
	}
	log_debug(1 << CXGBI_DBG_SOCK,
		"route to %pI4 :%u, ndev p#%d,%s, cdev 0x%p.\n",
		&daddr->sin_addr.s_addr, ntohs(daddr->sin_port),
			   port, ndev->name, cdev);

	csk = cxgbi_sock_create(cdev);
	if (!csk) {
		err = -ENOMEM;
		goto rel_neigh;
	}
	csk->cdev = cdev;
	csk->port_id = port;
	csk->mtu = mtu;
	csk->dst = dst;

	csk->csk_family = AF_INET;
	csk->daddr.sin_addr.s_addr = daddr->sin_addr.s_addr;
	csk->daddr.sin_port = daddr->sin_port;
	csk->daddr.sin_family = daddr->sin_family;
	csk->saddr.sin_family = daddr->sin_family;
	csk->saddr.sin_addr.s_addr = fl4.saddr;
	neigh_release(n);

	return csk;

rel_neigh:
	neigh_release(n);

rel_rt:
	ip_rt_put(rt);
err_out:
	return ERR_PTR(err);
}