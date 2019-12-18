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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct mt7601u_dev {int /*<<< orphan*/  state; TYPE_1__ mcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_MCU_RUNNING ; 
 int mt7601u_load_firmware (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt7601u_mcu_init(struct mt7601u_dev *dev)
{
	int ret;

	mutex_init(&dev->mcu.mutex);

	ret = mt7601u_load_firmware(dev);
	if (ret)
		return ret;

	set_bit(MT7601U_STATE_MCU_RUNNING, &dev->state);

	return 0;
}