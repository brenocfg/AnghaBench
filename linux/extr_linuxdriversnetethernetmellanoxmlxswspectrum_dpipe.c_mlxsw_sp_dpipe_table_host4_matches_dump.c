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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int mlxsw_sp_dpipe_table_host_matches_dump (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_dpipe_table_host4_matches_dump(void *priv, struct sk_buff *skb)
{
	return mlxsw_sp_dpipe_table_host_matches_dump(skb, AF_INET);
}