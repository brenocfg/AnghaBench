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
 int /*<<< orphan*/  Q_SELECT ; 
 int mt76x02_mcu_function_select (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_mcu_set_radio_state (struct mt76x02_dev*,int) ; 

int mt76x2u_mcu_init(struct mt76x02_dev *dev)
{
	int err;

	err = mt76x02_mcu_function_select(dev, Q_SELECT, 1);
	if (err < 0)
		return err;

	return mt76x02_mcu_set_radio_state(dev, true);
}