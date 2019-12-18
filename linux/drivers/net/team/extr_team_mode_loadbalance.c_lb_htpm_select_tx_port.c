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
struct team {int dummy; } ;
struct sk_buff {int dummy; } ;
struct lb_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LB_HTPM_PORT_BY_HASH (struct lb_priv*,unsigned char) ; 
 struct team_port* lb_hash_select_tx_port (struct team*,struct lb_priv*,struct sk_buff*,unsigned char) ; 
 scalar_t__ likely (struct team_port*) ; 
 struct team_port* rcu_dereference_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct team_port *lb_htpm_select_tx_port(struct team *team,
						struct lb_priv *lb_priv,
						struct sk_buff *skb,
						unsigned char hash)
{
	struct team_port *port;

	port = rcu_dereference_bh(LB_HTPM_PORT_BY_HASH(lb_priv, hash));
	if (likely(port))
		return port;
	/* If no valid port in the table, fall back to simple hash */
	return lb_hash_select_tx_port(team, lb_priv, skb, hash);
}