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
typedef  int u8 ;
struct mt76x02_tx_status {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x02_dev {int /*<<< orphan*/  txstatus_fifo; int /*<<< orphan*/  txstatus_fifo_lock; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  kfifo_is_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct mt76x02_tx_status) ; 
 int mt76x02_mac_load_tx_status (struct mt76x02_dev*,struct mt76x02_tx_status*) ; 
 int /*<<< orphan*/  mt76x02_send_tx_status (struct mt76x02_dev*,struct mt76x02_tx_status*,int*) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mac_txstat_poll (struct mt76x02_dev*) ; 

void mt76x02_mac_poll_tx_status(struct mt76x02_dev *dev, bool irq)
{
	struct mt76x02_tx_status stat = {};
	u8 update = 1;
	bool ret;

	if (!test_bit(MT76_STATE_RUNNING, &dev->mt76.state))
		return;

	trace_mac_txstat_poll(dev);

	while (!irq || !kfifo_is_full(&dev->txstatus_fifo)) {
		if (!spin_trylock(&dev->txstatus_fifo_lock))
			break;

		ret = mt76x02_mac_load_tx_status(dev, &stat);
		spin_unlock(&dev->txstatus_fifo_lock);

		if (!ret)
			break;

		if (!irq) {
			mt76x02_send_tx_status(dev, &stat, &update);
			continue;
		}

		kfifo_put(&dev->txstatus_fifo, stat);
	}
}