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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int mt76x2u_mcu_load_firmware (struct mt76x02_dev*) ; 
 int mt76x2u_mcu_load_rom_patch (struct mt76x02_dev*) ; 

int mt76x2u_mcu_fw_init(struct mt76x02_dev *dev)
{
	int err;

	err = mt76x2u_mcu_load_rom_patch(dev);
	if (err < 0)
		return err;

	return mt76x2u_mcu_load_firmware(dev);
}