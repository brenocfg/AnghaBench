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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int offload_fwd_mark; } ;

/* Variables and functions */
 void mlxsw_sp_rx_listener_no_mark_func (struct sk_buff*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void mlxsw_sp_rx_listener_mark_func(struct sk_buff *skb, u8 local_port,
					   void *priv)
{
	skb->offload_fwd_mark = 1;
	return mlxsw_sp_rx_listener_no_mark_func(skb, local_port, priv);
}