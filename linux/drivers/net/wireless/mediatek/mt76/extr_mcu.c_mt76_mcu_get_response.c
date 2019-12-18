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
struct TYPE_3__ {int /*<<< orphan*/  res_q; int /*<<< orphan*/  wait; } ;
struct TYPE_4__ {TYPE_1__ mcu; } ;
struct mt76_dev {TYPE_2__ mmio; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

struct sk_buff *mt76_mcu_get_response(struct mt76_dev *dev,
				      unsigned long expires)
{
	unsigned long timeout;

	if (!time_is_after_jiffies(expires))
		return NULL;

	timeout = expires - jiffies;
	wait_event_timeout(dev->mmio.mcu.wait,
			   !skb_queue_empty(&dev->mmio.mcu.res_q),
			   timeout);
	return skb_dequeue(&dev->mmio.mcu.res_q);
}