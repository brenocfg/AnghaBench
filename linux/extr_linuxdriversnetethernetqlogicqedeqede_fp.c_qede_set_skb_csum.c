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
struct sk_buff {int csum_level; int encapsulation; int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int QEDE_CSUM_UNNECESSARY ; 
 int QEDE_TUNN_CSUM_UNNECESSARY ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static void qede_set_skb_csum(struct sk_buff *skb, u8 csum_flag)
{
	skb_checksum_none_assert(skb);

	if (csum_flag & QEDE_CSUM_UNNECESSARY)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	if (csum_flag & QEDE_TUNN_CSUM_UNNECESSARY) {
		skb->csum_level = 1;
		skb->encapsulation = 1;
	}
}