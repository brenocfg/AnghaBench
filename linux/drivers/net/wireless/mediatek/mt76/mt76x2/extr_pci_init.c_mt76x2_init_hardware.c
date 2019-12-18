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
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  rxfilter; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_dma_disable (struct mt76x02_dev*) ; 
 int mt76x02_dma_init (struct mt76x02_dev*) ; 
 int mt76x2_eeprom_init (struct mt76x02_dev*) ; 
 int mt76x2_mac_reset (struct mt76x02_dev*,int) ; 
 int mt76x2_mac_start (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x02_dev*,int) ; 
 int mt76x2_mcu_init (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_power_on (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_reset_wlan (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x2_init_hardware(struct mt76x02_dev *dev)
{
	int ret;

	mt76x02_dma_disable(dev);
	mt76x2_reset_wlan(dev, true);
	mt76x2_power_on(dev);

	ret = mt76x2_eeprom_init(dev);
	if (ret)
		return ret;

	ret = mt76x2_mac_reset(dev, true);
	if (ret)
		return ret;

	dev->mt76.rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	ret = mt76x02_dma_init(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);
	ret = mt76x2_mac_start(dev);
	if (ret)
		return ret;

	ret = mt76x2_mcu_init(dev);
	if (ret)
		return ret;

	mt76x2_mac_stop(dev, false);

	return 0;
}