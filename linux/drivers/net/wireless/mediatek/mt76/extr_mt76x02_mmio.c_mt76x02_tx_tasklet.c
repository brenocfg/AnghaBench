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
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_txq_schedule_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_mac_poll_tx_status (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x02_process_tx_status_fifo (struct mt76x02_dev*) ; 

__attribute__((used)) static void mt76x02_tx_tasklet(unsigned long data)
{
	struct mt76x02_dev *dev = (struct mt76x02_dev *)data;

	mt76x02_mac_poll_tx_status(dev, false);
	mt76x02_process_tx_status_fifo(dev);

	mt76_txq_schedule_all(&dev->mt76);
}