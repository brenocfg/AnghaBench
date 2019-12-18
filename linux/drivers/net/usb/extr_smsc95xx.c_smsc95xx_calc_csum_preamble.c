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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int csum_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_checksum_start_offset (struct sk_buff*) ; 

__attribute__((used)) static u32 smsc95xx_calc_csum_preamble(struct sk_buff *skb)
{
	u16 low_16 = (u16)skb_checksum_start_offset(skb);
	u16 high_16 = low_16 + skb->csum_offset;
	return (high_16 << 16) | low_16;
}