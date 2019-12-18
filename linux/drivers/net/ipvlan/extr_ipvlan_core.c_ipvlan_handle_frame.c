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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct ipvl_port {int mode; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;

/* Variables and functions */
#define  IPVLAN_MODE_L2 130 
#define  IPVLAN_MODE_L3 129 
#define  IPVLAN_MODE_L3S 128 
 int /*<<< orphan*/  RX_HANDLER_CONSUMED ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  ipvlan_handle_mode_l2 (struct sk_buff**,struct ipvl_port*) ; 
 int /*<<< orphan*/  ipvlan_handle_mode_l3 (struct sk_buff**,struct ipvl_port*) ; 
 struct ipvl_port* ipvlan_port_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

rx_handler_result_t ipvlan_handle_frame(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct ipvl_port *port = ipvlan_port_get_rcu(skb->dev);

	if (!port)
		return RX_HANDLER_PASS;

	switch (port->mode) {
	case IPVLAN_MODE_L2:
		return ipvlan_handle_mode_l2(pskb, port);
	case IPVLAN_MODE_L3:
		return ipvlan_handle_mode_l3(pskb, port);
#ifdef CONFIG_IPVLAN_L3S
	case IPVLAN_MODE_L3S:
		return RX_HANDLER_PASS;
#endif
	}

	/* Should not reach here */
	WARN_ONCE(true, "ipvlan_handle_frame() called for mode = [%hx]\n",
			  port->mode);
	kfree_skb(skb);
	return RX_HANDLER_CONSUMED;
}