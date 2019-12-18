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
 int /*<<< orphan*/  mt76u_queues_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_mcu_set_radio_state (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2u_stop_hw (struct mt76x02_dev*) ; 

void mt76x2u_cleanup(struct mt76x02_dev *dev)
{
	mt76x02_mcu_set_radio_state(dev, false);
	mt76x2u_stop_hw(dev);
	mt76u_queues_deinit(&dev->mt76);
}