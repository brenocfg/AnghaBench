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
struct mt76_queue_entry {int /*<<< orphan*/  urb; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT_RX_SG_MAX_SIZE ; 
 int mt76u_refill_rx (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76u_urb_alloc (struct mt76_dev*,struct mt76_queue_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76u_rx_urb_alloc(struct mt76_dev *dev, struct mt76_queue_entry *e)
{
	int err;

	err = mt76u_urb_alloc(dev, e, MT_RX_SG_MAX_SIZE);
	if (err)
		return err;

	return mt76u_refill_rx(dev, e->urb, MT_RX_SG_MAX_SIZE,
			       GFP_KERNEL);
}