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
struct sk_buff {int len; scalar_t__ data; } ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  trace_mt_mcu_msg_send (struct mt7601u_dev*,struct sk_buff*,int,int) ; 

__attribute__((used)) static inline void trace_mt_mcu_msg_send_cs(struct mt7601u_dev *dev,
					    struct sk_buff *skb, bool need_resp)
{
	u32 i, csum = 0;

	for (i = 0; i < skb->len / 4; i++)
		csum ^= get_unaligned_le32(skb->data + i * 4);

	trace_mt_mcu_msg_send(dev, skb, csum, need_resp);
}