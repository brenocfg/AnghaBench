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
struct TYPE_2__ {int /*<<< orphan*/  pre_tbtt_tasklet; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_dma_cleanup (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_mcu_cleanup (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_chip_onoff (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x0e_stop_hw (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x0e_cleanup(struct mt76x02_dev *dev)
{
	clear_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76x0_chip_onoff(dev, false, false);
	mt76x0e_stop_hw(dev);
	mt76x02_dma_cleanup(dev);
	mt76x02_mcu_cleanup(dev);
}