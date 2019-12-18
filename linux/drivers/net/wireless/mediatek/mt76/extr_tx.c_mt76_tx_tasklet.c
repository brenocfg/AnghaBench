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
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_txq_schedule_all (struct mt76_dev*) ; 

void mt76_tx_tasklet(unsigned long data)
{
	struct mt76_dev *dev = (struct mt76_dev *)data;

	mt76_txq_schedule_all(dev);
}