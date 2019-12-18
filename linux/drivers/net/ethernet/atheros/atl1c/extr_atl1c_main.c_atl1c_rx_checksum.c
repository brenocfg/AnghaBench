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
struct atl1c_recv_ret_status {int dummy; } ;
struct atl1c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void atl1c_rx_checksum(struct atl1c_adapter *adapter,
		  struct sk_buff *skb, struct atl1c_recv_ret_status *prrs)
{
	/*
	 * The pid field in RRS in not correct sometimes, so we
	 * cannot figure out if the packet is fragmented or not,
	 * so we tell the KERNEL CHECKSUM_NONE
	 */
	skb_checksum_none_assert(skb);
}