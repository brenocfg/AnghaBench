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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct qedr_dev {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  QEDR_MSG_QP ; 
 struct neighbour* dst_neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int
qedr_addr4_resolve(struct qedr_dev *dev,
		   struct sockaddr_in *src_in,
		   struct sockaddr_in *dst_in, u8 *dst_mac)
{
	__be32 src_ip = src_in->sin_addr.s_addr;
	__be32 dst_ip = dst_in->sin_addr.s_addr;
	struct neighbour *neigh = NULL;
	struct rtable *rt = NULL;
	int rc = 0;

	rt = ip_route_output(&init_net, dst_ip, src_ip, 0, 0);
	if (IS_ERR(rt)) {
		DP_ERR(dev, "ip_route_output returned error\n");
		return -EINVAL;
	}

	neigh = dst_neigh_lookup(&rt->dst, &dst_ip);

	if (neigh) {
		rcu_read_lock();
		if (neigh->nud_state & NUD_VALID) {
			ether_addr_copy(dst_mac, neigh->ha);
			DP_DEBUG(dev, QEDR_MSG_QP, "mac_addr=[%pM]\n", dst_mac);
		} else {
			neigh_event_send(neigh, NULL);
		}
		rcu_read_unlock();
		neigh_release(neigh);
	}

	ip_rt_put(rt);

	return rc;
}