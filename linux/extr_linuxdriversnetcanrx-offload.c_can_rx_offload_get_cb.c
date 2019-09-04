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
struct sk_buff {scalar_t__ cb; } ;
struct can_rx_offload_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline struct can_rx_offload_cb *can_rx_offload_get_cb(struct sk_buff *skb)
{
	BUILD_BUG_ON(sizeof(struct can_rx_offload_cb) > sizeof(skb->cb));

	return (struct can_rx_offload_cb *)skb->cb;
}