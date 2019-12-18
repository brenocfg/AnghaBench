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
struct sk_buff {unsigned int len; unsigned int csum_offset; } ;

/* Variables and functions */
 unsigned int skb_checksum_start_offset (struct sk_buff*) ; 

__attribute__((used)) static bool smsc95xx_can_tx_checksum(struct sk_buff *skb)
{
       unsigned int len = skb->len - skb_checksum_start_offset(skb);

       if (skb->len <= 45)
	       return false;
       return skb->csum_offset < (len - (4 + 1));
}