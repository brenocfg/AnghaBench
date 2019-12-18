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
typedef  int /*<<< orphan*/  txwi ;
struct sk_buff {int len; struct mt76x02_txwi* data; } ;
struct mt76x02_txwi {int dummy; } ;
struct mt76x02_dev {TYPE_1__* beacon_ops; } ;
struct TYPE_2__ {int slot_size; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x02_dev*,int,struct mt76x02_txwi*,int) ; 
 int /*<<< orphan*/  mt76x02_mac_write_txwi (struct mt76x02_dev*,struct mt76x02_txwi*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mt76x02_write_beacon(struct mt76x02_dev *dev, int offset, struct sk_buff *skb)
{
	int beacon_len = dev->beacon_ops->slot_size;
	struct mt76x02_txwi txwi;

	if (WARN_ON_ONCE(beacon_len < skb->len + sizeof(struct mt76x02_txwi)))
		return -ENOSPC;

	mt76x02_mac_write_txwi(dev, &txwi, skb, NULL, NULL, skb->len);

	mt76_wr_copy(dev, offset, &txwi, sizeof(txwi));
	offset += sizeof(txwi);

	mt76_wr_copy(dev, offset, skb->data, skb->len);
	return 0;
}