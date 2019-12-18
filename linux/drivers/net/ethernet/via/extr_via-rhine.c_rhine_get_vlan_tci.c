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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 rhine_get_vlan_tci(struct sk_buff *skb, int data_size)
{
	u8 *trailer = (u8 *)skb->data + ((data_size + 3) & ~3) + 2;
	return be16_to_cpup((__be16 *)trailer);
}