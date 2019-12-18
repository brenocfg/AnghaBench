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
typedef  unsigned long u32 ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int RAVB_ALIGN ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned long) ; 

__attribute__((used)) static void ravb_set_buffer_align(struct sk_buff *skb)
{
	u32 reserve = (unsigned long)skb->data & (RAVB_ALIGN - 1);

	if (reserve)
		skb_reserve(skb, RAVB_ALIGN - reserve);
}