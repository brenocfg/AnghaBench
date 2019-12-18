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
typedef  int /*<<< orphan*/  u8 ;
struct xenvif_mcast_addr {int /*<<< orphan*/  entry; int /*<<< orphan*/  addr; } ;
struct xenvif {scalar_t__ fe_mcast_count; int /*<<< orphan*/  fe_mcast_addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ XEN_NETBK_MCAST_MAX ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct xenvif_mcast_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xenvif_mcast_add(struct xenvif *vif, const u8 *addr)
{
	struct xenvif_mcast_addr *mcast;

	if (vif->fe_mcast_count == XEN_NETBK_MCAST_MAX) {
		if (net_ratelimit())
			netdev_err(vif->dev,
				   "Too many multicast addresses\n");
		return -ENOSPC;
	}

	mcast = kzalloc(sizeof(*mcast), GFP_ATOMIC);
	if (!mcast)
		return -ENOMEM;

	ether_addr_copy(mcast->addr, addr);
	list_add_tail_rcu(&mcast->entry, &vif->fe_mcast_addr);
	vif->fe_mcast_count++;

	return 0;
}