#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {size_t isdn_device; } ;
typedef  TYPE_3__ isdn_net_local ;
struct TYPE_9__ {TYPE_2__** drv; } ;
struct TYPE_7__ {TYPE_1__* interface; } ;
struct TYPE_6__ {unsigned short hl_hdrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (unsigned short,int /*<<< orphan*/ ) ; 
 TYPE_5__* dev ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned short) ; 

__attribute__((used)) static struct sk_buff*
isdn_net_ciscohdlck_alloc_skb(isdn_net_local *lp, int len)
{
	unsigned short hl = dev->drv[lp->isdn_device]->interface->hl_hdrlen;
	struct sk_buff *skb;

	skb = alloc_skb(hl + len, GFP_ATOMIC);
	if (skb)
		skb_reserve(skb, hl);
	else
		printk("isdn out of mem at %s:%d!\n", __FILE__, __LINE__);
	return skb;
}