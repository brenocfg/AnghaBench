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
struct urb {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT_RXQ_MAIN ; 
 int /*<<< orphan*/  mt76_rx_poll_complete (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* mt76u_get_next_rx_entry (struct mt76_dev*) ; 
 int mt76u_process_rx_entry (struct mt76_dev*,struct urb*) ; 
 int mt76u_refill_rx (struct mt76_dev*,struct urb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76u_submit_rx_buf (struct mt76_dev*,struct urb*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void mt76u_rx_tasklet(unsigned long data)
{
	struct mt76_dev *dev = (struct mt76_dev *)data;
	struct urb *urb;
	int err, count;

	rcu_read_lock();

	while (true) {
		urb = mt76u_get_next_rx_entry(dev);
		if (!urb)
			break;

		count = mt76u_process_rx_entry(dev, urb);
		if (count > 0) {
			err = mt76u_refill_rx(dev, urb, count, GFP_ATOMIC);
			if (err < 0)
				break;
		}
		mt76u_submit_rx_buf(dev, urb);
	}
	mt76_rx_poll_complete(dev, MT_RXQ_MAIN, NULL);

	rcu_read_unlock();
}