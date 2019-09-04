#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nfp_repr {TYPE_4__* app; TYPE_2__* dst; } ;
struct nfp_flower_cmsg_portreify {int /*<<< orphan*/  info; scalar_t__ reserved; int /*<<< orphan*/  portnum; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_7__ {TYPE_1__ port_info; } ;
struct TYPE_6__ {TYPE_3__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_PORT_REIFY ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_flower_cmsg_portreify* nfp_flower_cmsg_get_data (struct sk_buff*) ; 

int nfp_flower_cmsg_portreify(struct nfp_repr *repr, bool exists)
{
	struct nfp_flower_cmsg_portreify *msg;
	struct sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(repr->app, sizeof(*msg),
				    NFP_FLOWER_CMSG_TYPE_PORT_REIFY,
				    GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	msg->portnum = cpu_to_be32(repr->dst->u.port_info.port_id);
	msg->reserved = 0;
	msg->info = cpu_to_be16(exists);

	nfp_ctrl_tx(repr->app->ctrl, skb);

	return 0;
}