#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  res_q; } ;
struct TYPE_4__ {TYPE_1__ mcu; } ;
struct mt76_dev {TYPE_2__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void mt76_mcu_rx_event(struct mt76_dev *dev, struct sk_buff *skb)
{
	skb_queue_tail(&dev->mmio.mcu.res_q, skb);
	wake_up(&dev->mmio.mcu.wait);
}