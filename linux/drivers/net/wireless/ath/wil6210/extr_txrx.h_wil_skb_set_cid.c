#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cid; } ;
struct skb_rx_info {TYPE_1__ rx_info; } ;
struct sk_buff {scalar_t__ cb; } ;

/* Variables and functions */

__attribute__((used)) static inline void wil_skb_set_cid(struct sk_buff *skb, u8 cid)
{
	struct skb_rx_info *skb_rx_info = (void *)skb->cb;

	skb_rx_info->rx_info.cid = cid;
}