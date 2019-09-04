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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rxe_pkt_info {int dummy; } ;
struct rxe_dev {int dummy; } ;
struct rxe_av {scalar_t__ network_type; } ;

/* Variables and functions */
 scalar_t__ RDMA_NETWORK_IPV4 ; 
 scalar_t__ RDMA_NETWORK_IPV6 ; 
 int prepare4 (struct rxe_dev*,struct rxe_pkt_info*,struct sk_buff*,struct rxe_av*) ; 
 int prepare6 (struct rxe_dev*,struct rxe_pkt_info*,struct sk_buff*,struct rxe_av*) ; 
 struct rxe_av* rxe_get_av (struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  rxe_icrc_hdr (struct rxe_pkt_info*,struct sk_buff*) ; 

int rxe_prepare(struct rxe_dev *rxe, struct rxe_pkt_info *pkt,
		struct sk_buff *skb, u32 *crc)
{
	int err = 0;
	struct rxe_av *av = rxe_get_av(pkt);

	if (av->network_type == RDMA_NETWORK_IPV4)
		err = prepare4(rxe, pkt, skb, av);
	else if (av->network_type == RDMA_NETWORK_IPV6)
		err = prepare6(rxe, pkt, skb, av);

	*crc = rxe_icrc_hdr(pkt, skb);

	return err;
}