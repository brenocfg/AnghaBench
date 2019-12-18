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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct mt76_reg_pair {scalar_t__ value; scalar_t__ reg; } ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_WRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INBAND_PACKET_MAX_LEN ; 
 scalar_t__ MT_DMA_HDR_LEN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int min (int const,int) ; 
 int mt7601u_mcu_msg_send (struct mt7601u_dev*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put_le32 (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

int mt7601u_write_reg_pairs(struct mt7601u_dev *dev, u32 base,
			    const struct mt76_reg_pair *data, int n)
{
	const int max_vals_per_cmd = INBAND_PACKET_MAX_LEN / 8;
	struct sk_buff *skb;
	int cnt, i, ret;

	if (!n)
		return 0;

	cnt = min(max_vals_per_cmd, n);

	skb = alloc_skb(cnt * 8 + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;
	skb_reserve(skb, MT_DMA_HDR_LEN);

	for (i = 0; i < cnt; i++) {
		skb_put_le32(skb, base + data[i].reg);
		skb_put_le32(skb, data[i].value);
	}

	ret = mt7601u_mcu_msg_send(dev, skb, CMD_RANDOM_WRITE, cnt == n);
	if (ret)
		return ret;

	return mt7601u_write_reg_pairs(dev, base, data + cnt, n - cnt);
}