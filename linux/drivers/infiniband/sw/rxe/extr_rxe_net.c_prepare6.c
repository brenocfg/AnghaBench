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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct rxe_qp {int /*<<< orphan*/  src_port; } ;
struct rxe_pkt_info {struct rxe_qp* qp; } ;
struct TYPE_10__ {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; } ;
struct in6_addr {int dummy; } ;
struct TYPE_8__ {struct in6_addr sin6_addr; } ;
struct TYPE_9__ {TYPE_3__ _sockaddr_in6; } ;
struct TYPE_6__ {struct in6_addr sin6_addr; } ;
struct TYPE_7__ {TYPE_1__ _sockaddr_in6; } ;
struct rxe_av {TYPE_5__ grh; TYPE_4__ dgid_addr; TYPE_2__ sgid_addr; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  ROCE_V2_UDP_DPORT ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  prepare_ipv6_hdr (struct dst_entry*,struct sk_buff*,struct in6_addr*,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_udp_hdr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dst_entry* rxe_find_route (int /*<<< orphan*/ ,struct rxe_qp*,struct rxe_av*) ; 
 struct rxe_av* rxe_get_av (struct rxe_pkt_info*) ; 

__attribute__((used)) static int prepare6(struct rxe_pkt_info *pkt, struct sk_buff *skb)
{
	struct rxe_qp *qp = pkt->qp;
	struct dst_entry *dst;
	struct rxe_av *av = rxe_get_av(pkt);
	struct in6_addr *saddr = &av->sgid_addr._sockaddr_in6.sin6_addr;
	struct in6_addr *daddr = &av->dgid_addr._sockaddr_in6.sin6_addr;

	dst = rxe_find_route(skb->dev, qp, av);
	if (!dst) {
		pr_err("Host not reachable\n");
		return -EHOSTUNREACH;
	}

	prepare_udp_hdr(skb, cpu_to_be16(qp->src_port),
			cpu_to_be16(ROCE_V2_UDP_DPORT));

	prepare_ipv6_hdr(dst, skb, saddr, daddr, IPPROTO_UDP,
			 av->grh.traffic_class,
			 av->grh.hop_limit);

	dst_release(dst);
	return 0;
}