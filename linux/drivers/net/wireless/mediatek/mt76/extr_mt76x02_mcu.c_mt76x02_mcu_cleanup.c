#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  res_q; } ;
struct TYPE_5__ {TYPE_1__ mcu; } ;
struct TYPE_6__ {TYPE_2__ mmio; } ;
struct mt76x02_dev {TYPE_3__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_INT_LEVEL ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int mt76x02_mcu_cleanup(struct mt76x02_dev *dev)
{
	struct sk_buff *skb;

	mt76_wr(dev, MT_MCU_INT_LEVEL, 1);
	usleep_range(20000, 30000);

	while ((skb = skb_dequeue(&dev->mt76.mmio.mcu.res_q)) != NULL)
		dev_kfree_skb(skb);

	return 0;
}