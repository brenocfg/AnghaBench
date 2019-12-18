#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; } ;
struct rxe_dev {int /*<<< orphan*/  ib_dev; } ;
struct in6_addr {int dummy; } ;
struct ib_gid_attr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 scalar_t__ IS_ERR (struct ib_gid_attr const*) ; 
 int PTR_ERR (struct ib_gid_attr const*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_set_v4mapped (int /*<<< orphan*/ ,struct in6_addr*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 struct ib_gid_attr* rdma_find_gid_by_port (int /*<<< orphan*/ *,union ib_gid*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 

__attribute__((used)) static int rxe_match_dgid(struct rxe_dev *rxe, struct sk_buff *skb)
{
	const struct ib_gid_attr *gid_attr;
	union ib_gid dgid;
	union ib_gid *pdgid;

	if (skb->protocol == htons(ETH_P_IP)) {
		ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
				       (struct in6_addr *)&dgid);
		pdgid = &dgid;
	} else {
		pdgid = (union ib_gid *)&ipv6_hdr(skb)->daddr;
	}

	gid_attr = rdma_find_gid_by_port(&rxe->ib_dev, pdgid,
					 IB_GID_TYPE_ROCE_UDP_ENCAP,
					 1, skb->dev);
	if (IS_ERR(gid_attr))
		return PTR_ERR(gid_attr);

	rdma_put_gid_attr(gid_attr);
	return 0;
}