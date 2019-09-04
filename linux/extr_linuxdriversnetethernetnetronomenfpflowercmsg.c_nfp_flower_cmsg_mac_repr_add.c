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
struct sk_buff {int dummy; } ;
struct nfp_flower_cmsg_mac_repr {TYPE_1__* ports; } ;
struct TYPE_2__ {unsigned int idx; unsigned int info; unsigned int nbi_port; unsigned int phys_port; } ;

/* Variables and functions */
 unsigned int NFP_FLOWER_CMSG_MAC_REPR_NBI ; 
 struct nfp_flower_cmsg_mac_repr* nfp_flower_cmsg_get_data (struct sk_buff*) ; 

void
nfp_flower_cmsg_mac_repr_add(struct sk_buff *skb, unsigned int idx,
			     unsigned int nbi, unsigned int nbi_port,
			     unsigned int phys_port)
{
	struct nfp_flower_cmsg_mac_repr *msg;

	msg = nfp_flower_cmsg_get_data(skb);
	msg->ports[idx].idx = idx;
	msg->ports[idx].info = nbi & NFP_FLOWER_CMSG_MAC_REPR_NBI;
	msg->ports[idx].nbi_port = nbi_port;
	msg->ports[idx].phys_port = phys_port;
}