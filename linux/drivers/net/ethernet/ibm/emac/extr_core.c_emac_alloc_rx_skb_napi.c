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
struct emac_instance {int /*<<< orphan*/  rx_skb_size; TYPE_1__* mal; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int __emac_prepare_rx_skb (struct sk_buff*,struct emac_instance*,int) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emac_alloc_rx_skb_napi(struct emac_instance *dev, int slot)
{
	struct sk_buff *skb;

	skb = napi_alloc_skb(&dev->mal->napi, dev->rx_skb_size);

	return __emac_prepare_rx_skb(skb, dev, slot);
}