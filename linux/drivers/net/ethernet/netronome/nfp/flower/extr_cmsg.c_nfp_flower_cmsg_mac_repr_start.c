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
struct sk_buff {int dummy; } ;
struct nfp_flower_cmsg_mac_repr {unsigned int num_ports; int /*<<< orphan*/  reserved; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_MAC_REPR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_flower_cmsg_mac_repr* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  ports ; 
 int /*<<< orphan*/  struct_size (struct nfp_flower_cmsg_mac_repr*,int /*<<< orphan*/ ,unsigned int) ; 

struct sk_buff *
nfp_flower_cmsg_mac_repr_start(struct nfp_app *app, unsigned int num_ports)
{
	struct nfp_flower_cmsg_mac_repr *msg;
	struct sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(app, struct_size(msg, ports, num_ports),
				    NFP_FLOWER_CMSG_TYPE_MAC_REPR, GFP_KERNEL);
	if (!skb)
		return NULL;

	msg = nfp_flower_cmsg_get_data(skb);
	memset(msg->reserved, 0, sizeof(msg->reserved));
	msg->num_ports = num_ports;

	return skb;
}