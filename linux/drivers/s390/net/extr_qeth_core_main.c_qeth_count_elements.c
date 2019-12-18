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
struct sk_buff {scalar_t__ data; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 unsigned int qeth_get_elements_for_frags (struct sk_buff*) ; 
 scalar_t__ qeth_get_elements_for_range (scalar_t__,scalar_t__) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 

unsigned int qeth_count_elements(struct sk_buff *skb, unsigned int data_offset)
{
	unsigned int elements = qeth_get_elements_for_frags(skb);
	addr_t end = (addr_t)skb->data + skb_headlen(skb);
	addr_t start = (addr_t)skb->data + data_offset;

	if (start != end)
		elements += qeth_get_elements_for_range(start, end);
	return elements;
}