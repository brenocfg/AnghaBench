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
 int /*<<< orphan*/  MT_RF_BBP_CR ; 
 int mt76x02_mcu_set_radio_state (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_mcu_load_cr (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt76x2_phy_start(struct mt76x02_dev *dev)
{
	int ret;

	ret = mt76x02_mcu_set_radio_state(dev, true);
	if (ret)
		return ret;

	mt76x2_mcu_load_cr(dev, MT_RF_BBP_CR, 0, 0);

	return ret;
}