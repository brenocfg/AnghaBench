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

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned long) ; 

__attribute__((used)) static inline void fza_skb_align(struct sk_buff *skb, unsigned int v)
{
	unsigned long x, y;

	x = (unsigned long)skb->data;
	y = ALIGN(x, v);

	skb_reserve(skb, y - x);
}