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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int skb_get_hash (struct sk_buff*) ; 

u8 opa_vnic_calc_entropy(struct sk_buff *skb)
{
	u32 hash = skb_get_hash(skb);

	/* store XOR of all bytes in lower 8 bits */
	hash ^= hash >> 8;
	hash ^= hash >> 16;

	/* return lower 8 bits as entropy */
	return (u8)(hash & 0xFF);
}