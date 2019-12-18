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
struct sk_buff {int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int WLAN_EID_TIM ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int* p54_find_ie (struct sk_buff*,int) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int p54_beacon_format_ie_tim(struct sk_buff *skb)
{
	/*
	 * the good excuse for this mess is ... the firmware.
	 * The dummy TIM MUST be at the end of the beacon frame,
	 * because it'll be overwritten!
	 */
	u8 *tim;
	u8 dtim_len;
	u8 dtim_period;
	u8 *next;

	tim = p54_find_ie(skb, WLAN_EID_TIM);
	if (!tim)
		return 0;

	dtim_len = tim[1];
	dtim_period = tim[3];
	next = tim + 2 + dtim_len;

	if (dtim_len < 3)
		return -EINVAL;

	memmove(tim, next, skb_tail_pointer(skb) - next);
	tim = skb_tail_pointer(skb) - (dtim_len + 2);

	/* add the dummy at the end */
	tim[0] = WLAN_EID_TIM;
	tim[1] = 3;
	tim[2] = 0;
	tim[3] = dtim_period;
	tim[4] = 0;

	if (dtim_len > 3)
		skb_trim(skb, skb->len - (dtim_len - 3));

	return 0;
}