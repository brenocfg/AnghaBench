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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct qedr_dev {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; } ;
struct flowi6 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dst_entry {scalar_t__ error; } ;
typedef  int /*<<< orphan*/  fl6 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,scalar_t__) ; 
 int EINVAL ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  QEDR_MSG_QP ; 
 struct neighbour* dst_neigh_lookup (struct dst_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 struct dst_entry* ip6_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi6*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int
qedr_addr6_resolve(struct qedr_dev *dev,
		   struct sockaddr_in6 *src_in,
		   struct sockaddr_in6 *dst_in, u8 *dst_mac)
{
	struct neighbour *neigh = NULL;
	struct dst_entry *dst;
	struct flowi6 fl6;
	int rc = 0;

	memset(&fl6, 0, sizeof(fl6));
	fl6.daddr = dst_in->sin6_addr;
	fl6.saddr = src_in->sin6_addr;

	dst = ip6_route_output(&init_net, NULL, &fl6);

	if ((!dst) || dst->error) {
		if (dst) {
			dst_release(dst);
			DP_ERR(dev,
			       "ip6_route_output returned dst->error = %d\n",
			       dst->error);
		}
		return -EINVAL;
	}
	neigh = dst_neigh_lookup(dst, &fl6.daddr);
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

	dst_release(dst);

	return rc;
}