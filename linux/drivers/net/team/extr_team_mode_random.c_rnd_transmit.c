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
struct team_port {int dummy; } ;
struct team {int /*<<< orphan*/  en_port_count; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int prandom_u32_max (int /*<<< orphan*/ ) ; 
 scalar_t__ team_dev_queue_xmit (struct team*,struct team_port*,struct sk_buff*) ; 
 struct team_port* team_get_first_port_txable_rcu (struct team*,struct team_port*) ; 
 struct team_port* team_get_port_by_index_rcu (struct team*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool rnd_transmit(struct team *team, struct sk_buff *skb)
{
	struct team_port *port;
	int port_index;

	port_index = prandom_u32_max(team->en_port_count);
	port = team_get_port_by_index_rcu(team, port_index);
	if (unlikely(!port))
		goto drop;
	port = team_get_first_port_txable_rcu(team, port);
	if (unlikely(!port))
		goto drop;
	if (team_dev_queue_xmit(team, port, skb))
		return false;
	return true;

drop:
	dev_kfree_skb_any(skb);
	return false;
}