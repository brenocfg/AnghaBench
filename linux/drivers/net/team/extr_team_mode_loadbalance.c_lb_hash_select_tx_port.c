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
 struct team_port* team_get_port_by_index_rcu (struct team*,int) ; 
 int team_num_to_port_index (struct team*,unsigned char) ; 

__attribute__((used)) static struct team_port *lb_hash_select_tx_port(struct team *team,
						struct lb_priv *lb_priv,
						struct sk_buff *skb,
						unsigned char hash)
{
	int port_index = team_num_to_port_index(team, hash);

	return team_get_port_by_index_rcu(team, port_index);
}