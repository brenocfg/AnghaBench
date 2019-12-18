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
struct sk_buff {int* data; } ;

/* Variables and functions */

__attribute__((used)) static int e1000_check_lbtest_frame(struct sk_buff *skb,
				    unsigned int frame_size)
{
	frame_size &= ~1;
	if (*(skb->data + 3) == 0xFF)
		if ((*(skb->data + frame_size / 2 + 10) == 0xBE) &&
		    (*(skb->data + frame_size / 2 + 12) == 0xAF))
			return 0;
	return 13;
}