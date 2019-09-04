#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int* data; } ;
struct TYPE_5__ {TYPE_1__* fax; } ;
typedef  TYPE_2__ modem_info ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  bor; } ;

/* Variables and functions */

void
isdn_tty_fax_bitorder(modem_info *info, struct sk_buff *skb)
{
	__u8 LeftMask;
	__u8 RightMask;
	__u8 fBit;
	__u8 Data;
	int i;

	if (!info->fax->bor) {
		for (i = 0; i < skb->len; i++) {
			Data = skb->data[i];
			for (
				LeftMask = 0x80, RightMask = 0x01;
				LeftMask > RightMask;
				LeftMask >>= 1, RightMask <<= 1
				) {
				fBit = (Data & LeftMask);
				if (Data & RightMask)
					Data |= LeftMask;
				else
					Data &= ~LeftMask;
				if (fBit)
					Data |= RightMask;
				else
					Data &= ~RightMask;

			}
			skb->data[i] = Data;
		}
	}
}