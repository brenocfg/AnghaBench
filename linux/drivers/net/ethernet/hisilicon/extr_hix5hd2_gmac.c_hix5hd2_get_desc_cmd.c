#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int DESC_BUFF_LEN_OFF ; 
 int DESC_DATA_LEN_OFF ; 
 int DESC_DATA_MASK ; 
 int DESC_FL_FULL ; 
 int DESC_FRAGS_NUM_OFF ; 
 int DESC_SG ; 
 int DESC_VLD_BUSY ; 
 scalar_t__ HAS_CAP_TSO (unsigned long) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static u32 hix5hd2_get_desc_cmd(struct sk_buff *skb, unsigned long hw_cap)
{
	u32 cmd = 0;

	if (HAS_CAP_TSO(hw_cap)) {
		if (skb_shinfo(skb)->nr_frags)
			cmd |= DESC_SG;
		cmd |= skb_shinfo(skb)->nr_frags << DESC_FRAGS_NUM_OFF;
	} else {
		cmd |= DESC_FL_FULL |
			((skb->len & DESC_DATA_MASK) << DESC_BUFF_LEN_OFF);
	}

	cmd |= (skb->len & DESC_DATA_MASK) << DESC_DATA_LEN_OFF;
	cmd |= DESC_VLD_BUSY;

	return cmd;
}