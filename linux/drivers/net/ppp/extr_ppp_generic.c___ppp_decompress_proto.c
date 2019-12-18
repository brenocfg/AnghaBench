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
typedef  int u8 ;
struct sk_buff {int* data; } ;

/* Variables and functions */
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void __ppp_decompress_proto(struct sk_buff *skb)
{
	if (skb->data[0] & 0x01)
		*(u8 *)skb_push(skb, 1) = 0x00;
}