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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  arp_failure_handler_func ;
struct TYPE_2__ {int /*<<< orphan*/  arp_failure_handler; } ;

/* Variables and functions */
 TYPE_1__* L2T_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static inline void set_arp_failure_handler(struct sk_buff *skb,
					   arp_failure_handler_func hnd)
{
	L2T_SKB_CB(skb)->arp_failure_handler = hnd;
}