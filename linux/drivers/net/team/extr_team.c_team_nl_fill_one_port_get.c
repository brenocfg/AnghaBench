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
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ linkup; } ;
struct team_port {int changed; TYPE_1__ state; scalar_t__ removed; TYPE_2__* dev; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TEAM_ATTR_ITEM_PORT ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_CHANGED ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_DUPLEX ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_IFINDEX ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_LINKUP ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_REMOVED ; 
 int /*<<< orphan*/  TEAM_ATTR_PORT_SPEED ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int team_nl_fill_one_port_get(struct sk_buff *skb,
				     struct team_port *port)
{
	struct nlattr *port_item;

	port_item = nla_nest_start_noflag(skb, TEAM_ATTR_ITEM_PORT);
	if (!port_item)
		goto nest_cancel;
	if (nla_put_u32(skb, TEAM_ATTR_PORT_IFINDEX, port->dev->ifindex))
		goto nest_cancel;
	if (port->changed) {
		if (nla_put_flag(skb, TEAM_ATTR_PORT_CHANGED))
			goto nest_cancel;
		port->changed = false;
	}
	if ((port->removed &&
	     nla_put_flag(skb, TEAM_ATTR_PORT_REMOVED)) ||
	    (port->state.linkup &&
	     nla_put_flag(skb, TEAM_ATTR_PORT_LINKUP)) ||
	    nla_put_u32(skb, TEAM_ATTR_PORT_SPEED, port->state.speed) ||
	    nla_put_u8(skb, TEAM_ATTR_PORT_DUPLEX, port->state.duplex))
		goto nest_cancel;
	nla_nest_end(skb, port_item);
	return 0;

nest_cancel:
	nla_nest_cancel(skb, port_item);
	return -EMSGSIZE;
}