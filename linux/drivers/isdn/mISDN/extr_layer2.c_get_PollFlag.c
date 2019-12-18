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
typedef  int u_char ;
struct sk_buff {int* data; } ;
struct layer2 {int dummy; } ;

/* Variables and functions */
 size_t l2addrsize (struct layer2*) ; 

inline u_char
get_PollFlag(struct layer2 *l2, struct sk_buff *skb)
{
	return skb->data[l2addrsize(l2)] & 0x10;
}