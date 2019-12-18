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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; scalar_t__ cb; } ;
struct rtw_c2h_cmd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct rtw_c2h_cmd *get_c2h_from_skb(struct sk_buff *skb)
{
	u32 pkt_offset;

	pkt_offset = *((u32 *)skb->cb);
	return (struct rtw_c2h_cmd *)(skb->data + pkt_offset);
}