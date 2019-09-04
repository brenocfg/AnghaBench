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
struct e1000_adapter {int /*<<< orphan*/  alloc_rx_buff_failed; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *e1000_alloc_rx_skb(struct e1000_adapter *adapter,
					  unsigned int bufsz)
{
	struct sk_buff *skb = napi_alloc_skb(&adapter->napi, bufsz);

	if (unlikely(!skb))
		adapter->alloc_rx_buff_failed++;
	return skb;
}