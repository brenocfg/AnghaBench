#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sband; } ;
struct TYPE_4__ {int /*<<< orphan*/  sband; } ;
struct TYPE_6__ {TYPE_2__ sband_5g; TYPE_1__ sband_2g; } ;
struct mt76x02_dev {TYPE_3__ mt76; int /*<<< orphan*/  cal_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mt76_register_device (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_config_mac_addr_list (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_init_debugfs (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_init_device (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_rates ; 
 int mt76x2_init_hardware (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_txpower (struct mt76x02_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2_phy_calibrate ; 
 int /*<<< orphan*/  mt76x2_stop_hardware (struct mt76x02_dev*) ; 

int mt76x2_register_device(struct mt76x02_dev *dev)
{
	int ret;

	INIT_DELAYED_WORK(&dev->cal_work, mt76x2_phy_calibrate);

	mt76x02_init_device(dev);

	ret = mt76x2_init_hardware(dev);
	if (ret)
		return ret;

	mt76x02_config_mac_addr_list(dev);

	ret = mt76_register_device(&dev->mt76, true, mt76x02_rates,
				   ARRAY_SIZE(mt76x02_rates));
	if (ret)
		goto fail;

	mt76x02_init_debugfs(dev);
	mt76x2_init_txpower(dev, &dev->mt76.sband_2g.sband);
	mt76x2_init_txpower(dev, &dev->mt76.sband_5g.sband);

	return 0;

fail:
	mt76x2_stop_hardware(dev);
	return ret;
}