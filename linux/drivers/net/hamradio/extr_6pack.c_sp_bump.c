#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct sixpack {int rcount; TYPE_2__* dev; scalar_t__ cooked_buf; } ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,TYPE_2__*) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void sp_bump(struct sixpack *sp, char cmd)
{
	struct sk_buff *skb;
	int count;
	unsigned char *ptr;

	count = sp->rcount + 1;

	sp->dev->stats.rx_bytes += count;

	if ((skb = dev_alloc_skb(count + 1)) == NULL)
		goto out_mem;

	ptr = skb_put(skb, count + 1);
	*ptr++ = cmd;	/* KISS command */

	memcpy(ptr, sp->cooked_buf + 1, count);
	skb->protocol = ax25_type_trans(skb, sp->dev);
	netif_rx(skb);
	sp->dev->stats.rx_packets++;

	return;

out_mem:
	sp->dev->stats.rx_dropped++;
}