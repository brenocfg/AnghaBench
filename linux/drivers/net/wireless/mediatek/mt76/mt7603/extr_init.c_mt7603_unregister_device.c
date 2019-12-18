#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pre_tbtt_tasklet; } ;
struct mt7603_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7603_dma_cleanup (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mcu_exit (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_free_device (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

void mt7603_unregister_device(struct mt7603_dev *dev)
{
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76_unregister_device(&dev->mt76);
	mt7603_mcu_exit(dev);
	mt7603_dma_cleanup(dev);
	mt76_free_device(&dev->mt76);
}